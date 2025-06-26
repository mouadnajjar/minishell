/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:36:02 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/26 14:38:38 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"

static void	setup_child_io(t_cmd *cmd_list, int prev_fd, int pipefd[2])
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
}

static void	child_process(t_cmd *cmd_list, int prev_fd, int pipefd[2],
	char **envp)
{
	int	exitos;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_child_io(cmd_list, prev_fd, pipefd);
	if (apply_redirections(cmd_list->redirs) != 0)
	{
		exit(EXIT_FAILURE);
	}
	if (!cmd_list->argv || !cmd_list->argv[0])
	{
		if (g_shell.envp)
			free(g_shell.envp);
		free_gc_memory();
		exit(0);
	}
	if (is_built_in(cmd_list->argv[0]))
	{
		exitos = exec_builtins(cmd_list, &envp);
		free_env(g_shell.envp);
		exit (exitos);
	}
	else
		run_command(cmd_list->argv, envp);
	exit(EXIT_FAILURE);
}

void	fork_and_exec_command(t_cmd *cmd_list, pid_t *pids, int i,
		t_exec_ctx *ctx)
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
		exit(EXIT_FAILURE);
	}
	if (pids[i] == 0)
		child_process(cmd_list, ctx->prev_fd, ctx->pipefd, ctx->envp);
}

void	run_builtin_parent(t_cmd *cmd, char ***envp, pid_t *pids)
{
	int	saved_in;
	int	saved_out;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (saved_in == -1 || saved_out == -1)
	{
		perror("dup");
		if (pids)
			free(pids);
		exit(EXIT_FAILURE);
	}
	if (apply_redirections(cmd->redirs) != 0)
	{
		g_shell.last_exit_status = 1;
		return ;
	}
	exec_builtins(cmd, envp);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}

void	execute_commands(t_cmd *cmd_list, char ***envp)
{
	t_exec_ctx	ctx;
	int			cmd_counts;
	int			i;
	t_cmd		*tmp;

	init_execution_context(&ctx, envp);
	cmd_counts = getsize(cmd_list);
	g_shell.pids = allocate_pid(cmd_counts);
	i = 0;
	tmp = cmd_list;
	while (cmd_list)
	{
		if (is_built_in(cmd_list->argv[0]) && tmp->next == NULL)
		{
			run_builtin_parent(cmd_list, envp, g_shell.pids);
			return ;
		}
		handle_command_list(cmd_list, &ctx, &i);
		if (g_shell.heredoc_sigint)
			return ;
		cmd_list = cmd_list->next;
		i++;
	}
	wait_pids(g_shell.pids, cmd_counts);
	free(g_shell.pids);
}
