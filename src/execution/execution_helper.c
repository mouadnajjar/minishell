/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:26:41 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/26 14:44:29 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"
#include "../../includes/parser.h"

void	init_execution_context(t_exec_ctx *ctx, char ***envp)
{
	ctx->prev_fd = -1;
	ctx->envp = *envp;
}

void	process_command(t_cmd *cmd_list, pid_t *pids, int i,
	t_exec_ctx *ctx)
{
	if (g_shell.heredoc_sigint)
		return ;
	fork_and_exec_command(cmd_list, pids, i, ctx);
	ctx->prev_fd = close_and_update_pipe(cmd_list, ctx->prev_fd, ctx->pipefd);
}

void	execve_error(char *cmd_path)
{
	perror("execve");
	g_shell.last_exit_status = 1;
	free(cmd_path);
	exit(EXIT_FAILURE);
}

void	handle_command_list(t_cmd *cmd_list, t_exec_ctx *ctx, int *i)
{
	process_command(cmd_list, g_shell.pids, *i, ctx);
	if (g_shell.heredoc_sigint)
	{
		return ;
	}
	(*i)++;
}
