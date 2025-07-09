/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_help2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/07/05 18:50:18 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"

void	cleanup_heredoc(int *fd, char *line)
{
	close(fd[1]);
	if (line)
		free(line);
	gc_free_all();
	g_shell.last_exit_status = 130;
	exit(g_shell.last_exit_status);
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

void	process_heredoc_line(t_redirect *redir, int write_fd, char *line)
{
	char	*expanded;

	if (redir->quoted == 0)
		expanded = expand_value(line, NULL);
	else
	{
		expanded = gc_strdup(line);
	}
	write(write_fd, expanded, ft_strlen(expanded));
	write(write_fd, "\n", 1);
	free(line);
}

int	is_delimiter_or_eof(t_redirect *redir, char *line)
{
	if (!line)
		return (1);
	if (ft_strncmp(line, redir->target, ft_strlen(redir->target) + 1) == 0
		&& (ft_strlen(line) == ft_strlen(redir->target)))
	{
		return (1);
	}
	return (0);
}
