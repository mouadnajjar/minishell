/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_help3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/07/05 19:08:59 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"

void	heredoc_ctrl_c(int sig)
{
	(void)sig;
	if (g_shell.envp)
		free_env(g_shell.envp);
	write(1, "\n", 1);
	gc_free_all();
	close(g_shell.heredoc_pipe_fd[0]);
	close(g_shell.heredoc_pipe_fd[1]);
	exit(130);
}

void	init_fd_sigint(t_redirect *redir)
{
	redir->heredoc_fd = -1;
	g_shell.heredoc_sigint = 1;
}
