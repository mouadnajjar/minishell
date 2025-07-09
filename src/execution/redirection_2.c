/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:37:21 by monajjar          #+#    #+#             */
/*   Updated: 2025/07/05 12:55:52 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"

int	restore_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (1);
}

int	handle_single_redir(t_redirect *redir, int *saved_stdin, int *saved_stdout,
		int *i)
{
	if (check_ambiguous(redir))
		return (restore_fds(*saved_stdin, *saved_stdout));
	if (redir->type == IN)
		handle_input_redir(redir->target);
	else if (redir->type == OUT || redir->type == TRUNCATE)
		handle_output_redir(redir->target);
	else if (redir->type == APPEND)
		handle_append_redir(redir->target);
	else if (redir->type == HEREDOC && redir->heredoc_fd != -1)
	{
		if (check_heredoc(redir, i))
			return (restore_fds(*saved_stdin, *saved_stdout));
	}
	if (g_shell.last_exit_status == 1)
		return (restore_fds(*saved_stdin, *saved_stdout));
	return (0);
}
