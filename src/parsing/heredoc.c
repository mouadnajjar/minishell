/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/23 15:41:07 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/executor.h"

int	count_heredocs(t_cmd *cmds)
{
	int			count;
	t_redirect	*r;
	int			i;

	count = 0;
	while (cmds)
	{
		r = cmds->redirs;
		i = 0;
		while (r && r[i].target)
		{
			if (r[i].type == HEREDOC)
				count++;
			i++;
		}
		cmds = cmds->next;
	}
	return (count);
}

void	process_heredocs(t_cmd *cmds)
{
	t_redirect	*r;
	int			i;
	int			heredoc_count;

	heredoc_count = count_heredocs(cmds);
	if (heredoc_count > MAX_HEREDOCS)
	{
		ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
		g_shell.last_exit_status = 2;
		gc_free_all();
		return ;
	}
	while (cmds)
	{
		r = cmds->redirs;
		i = 0;
		while (r && r[i].target)
		{
			if (r[i].type == HEREDOC)
			{
				handle_heredoc(&r[i]);
				if (g_shell.heredoc_sigint)
					return ;  // Preserve exit status
			}
			i++;
		}
		cmds = cmds->next;
	}
}

void	init_heredoc_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("minishell: pipe");
		gc_free_all();
		exit(1);
	}
}

static void cleanup_heredoc(int *fd, char *line)
{
    close(fd[1]);  // Close write end
    if (line)
        free(line);
    gc_free_all();
    g_shell.last_exit_status = 130;  // Set before exit
    exit(130);
}

void	handle_heredoc(t_redirect *redir)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	init_heredoc_pipe(fd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0) // --- CHILD process
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		char *line;
		char *expanded;

		close(fd[0]); // close read end
		while (1)
		{
			line = readline("> ");
			if (g_shell.heredoc_sigint)  // Check interrupt flag
			{
				print_parse_error(ERR_HEREDOC_DELIM, redir->target);
				cleanup_heredoc(fd, line);
			}
			if (!line) // EOF (Ctrl+D)
			{
				print_parse_error(ERR_HEREDOC_DELIM, redir->target);
				break; // Just break, do not call cleanup_heredoc
			}
			if (ft_strncmp(line, redir->target, ft_strlen(redir->target) + 1) == 0
						&& (ft_strlen(line) == ft_strlen(redir->target)))
			{
				free(line);
				break;
			}
			if (redir->quoted == 0)
				expanded = expand_value(line, NULL);
			else
				expanded = gc_strdup(line);
			write(fd[1], expanded, ft_strlen(expanded));
			write(fd[1], "\n", 1);
			free(line);
		}
		close(fd[1]);
		gc_free_all();
		exit(0);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			write(1, "\n", 1);
			g_shell.last_exit_status = 130;
			close(fd[0]);
			redir->heredoc_fd = -1;
			g_shell.heredoc_sigint = 1;
			return;
		}
		if (WIFEXITED(status))
		{
			g_shell.last_exit_status = WEXITSTATUS(status);  // Get child's exit status
			if (g_shell.last_exit_status == 130)
			{
				close(fd[0]);
				redir->heredoc_fd = -1;
				g_shell.heredoc_sigint = 1;
				return;
			}
		}
		redir->heredoc_fd = fd[0];
	}
}


t_list	*extract_heredoc_delimiter(char *input, size_t *i)
{
	t_token	*next;
	t_list	*node;

	next = NULL;
	while (input[*i] && ft_isspace(input[*i]) )
		(*i)++;
	if (input[*i] == '\'' || input[*i] == '"')
		next = extract_quoted(input, i);
	else if (!is_special(input + *i) && input[*i] != '\0')
		next = extract_word(input, i);
	if (!next)
		return (NULL);
	next->is_heredoc_delim = 1;
	node = ft_lstnew(next);
	gc_add(node);
	return (node);
}
