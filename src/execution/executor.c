/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:36:02 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/13 18:45:18 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"
#include"../../includes/executor.h"

static void child_process(t_cmd *cmd_list, int prev_fd, int pipefd[2], char **envp)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd_list->is_pipe)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	apply_redirections(cmd_list->redirs);
	run_command(cmd_list->argv, envp);
	exit(EXIT_FAILURE);
}

static void	fork_and_exec_command(t_cmd *cmd_list, pid_t *pids, int i, t_exec_ctx *ctx)
{
	if (cmd_list->is_pipe && pipe(ctx->pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pids[i] = fork();
	if (pids[i] == -1)
	{
		perror("fork");
		exit (EXIT_FAILURE);
	}
	if (pids[i] == 0)
		child_process(cmd_list, ctx->prev_fd, ctx->pipefd, ctx->envp);
}

void	execute_commands(t_cmd *cmd_list, char ***envp)
{
	t_exec_ctx	ctx;
    int		cmd_counts;
	int		i;
	pid_t	*pids;
    
	ctx.prev_fd = -1;
	ctx.envp = *envp;
	cmd_counts = getsize(cmd_list);
	pids = allocate_pid(cmd_counts);
	i = 0;
    while (cmd_list)
    {
		if (is_built_in(cmd_list->argv[0]) && !cmd_list->is_pipe)
		{
			exec_builtins(cmd_list, envp);
			return ;
		}
		else
			fork_and_exec_command(cmd_list, pids, i, &ctx);
        ctx.prev_fd = close_and_update_pipe(cmd_list, ctx.prev_fd, ctx.pipefd);
		cmd_list = cmd_list->next;
		i++;
	}	
	wait_pids(pids, cmd_counts);
	free (pids);
}
