/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/07/05 20:11:02 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"

void	process_heredocs(t_cmd *cmds)
{
	t_redirect	*r;

	int (i), (heredoc_count);
	heredoc_count = count_heredocs(cmds);
	if (heredoc_count > MAX_HEREDOCS)
	{
		print_parse_error(ERR_MAX_HEREDOCS_EXCEEDED, NULL);
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
					return ;
			}
			i++;
		}
		cmds = cmds->next;
	}
}

void	child_heredoc_loop(t_redirect *redir, int write_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_shell.heredoc_sigint)
		{
			print_parse_error(ERR_HEREDOC_DELIM, redir->target);
			cleanup_heredoc(&write_fd, line);
		}
		if (!line)
		{
			print_parse_error(ERR_HEREDOC_DELIM, redir->target);
			break ;
		}
		if (is_delimiter_or_eof(redir, line))
		{
			free(line);
			break ;
		}
		process_heredoc_line(redir, write_fd, line);
	}
}

void	handle_heredoc_child(t_redirect *redir, int *fd)
{
	g_shell.heredoc_pipe_fd[0] = fd[0];
	g_shell.heredoc_pipe_fd[1] = fd[1];
	signal(SIGINT, heredoc_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	child_heredoc_loop(redir, fd[1]);
	close(fd[1]);
	if (g_shell.envp)
		free_env(g_shell.envp);
	gc_free_all();
	exit(0);
}

void	handle_heredoc_parent(t_redirect *redir, int *fd, pid_t pid)
{
	int	status;

	close(fd[1]);
	waitpid(pid, &status, 0);
	if ((WIFEXITED(status) && WEXITSTATUS(status) == 130)
		|| WIFSIGNALED(status))
	{
		close(fd[0]);
		redir->heredoc_fd = -1;
		g_shell.heredoc_sigint = 1;
		g_shell.last_exit_status = 130;
		return ;
	}
	redir->heredoc_fd = fd[0];
}

void	handle_heredoc(t_redirect *redir)
{
	int		fd[2];
	pid_t	pid;

	init_heredoc_pipe(fd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(fd[0]);
		close(fd[1]);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		handle_heredoc_child(redir, fd);
	else
		handle_heredoc_parent(redir, fd, pid);
}
