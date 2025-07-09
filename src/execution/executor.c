/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:36:02 by monajjar          #+#    #+#             */
/*   Updated: 2025/07/08 18:29:26 by ahlahfid         ###   ########.fr       */
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

	set_default_signals();
	setup_child_io(cmd_list, prev_fd, pipefd);
	if (apply_redirections(cmd_list->redirs) != 0)
	{
		free_all();
		exit(EXIT_FAILURE);
	}
	if (!cmd_list->argv || !cmd_list->argv[0])
	{
		free_all();
		exit(0);
	}
	if (is_built_in(cmd_list->argv[0]))
	{
		exitos = exec_builtins(cmd_list, &envp);
		if (exitos == BUILTIN_EXIT)
			exit(g_shell.last_exit_status);
		free_env(g_shell.envp);
		exit(exitos);
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
	t_saved	saved_fds;

	saved_fds.saved_stdin = dup(STDIN_FILENO);
	saved_fds.saved_stdout = dup(STDOUT_FILENO);
	if (saved_fds.saved_stdin == -1 || saved_fds.saved_stdout == -1)
	{
		perror("dup");
		if (pids)
			free(pids);
		exit(EXIT_FAILURE);
	}
	if (apply_redirections(cmd->redirs) != 0)
	{
		restore_fds(saved_fds.saved_stdin, saved_fds.saved_stdout);
		g_shell.last_exit_status = 1;
		return ;
	}
	saved_fds.status = exec_builtins(cmd, envp);
	dup2(saved_fds.saved_stdin, STDIN_FILENO);
	dup2(saved_fds.saved_stdout, STDOUT_FILENO);
	close(saved_fds.saved_stdin);
	close(saved_fds.saved_stdout);
	if (saved_fds.status == BUILTIN_EXIT)
		exit(g_shell.last_exit_status);
}

void	execute_commands(t_cmd *cmd_list, char ***envp)
{
	t_exec_ctx	ctx;
	int			cmd_counts;

	init_execution_context(&ctx, envp);
	cmd_counts = getsize(cmd_list);
	g_shell.pids = allocate_pid(cmd_counts);
	ctx.i = 0;
	if (is_built_in(cmd_list->argv[0]) && cmd_list->next == NULL)
		return (run_builtin_parent(cmd_list, envp, g_shell.pids));
	while (cmd_list)
	{
		update_last_arg_var(envp, cmd_list->argv);
		process_command(cmd_list, g_shell.pids, ctx.i, &ctx);
		if (check_heredoc_and_clean())
			return ;
		cleanup_heredoc_fds(cmd_list->redirs);
		cmd_list = cmd_list->next;
		ctx.i++;
	}
	signal(SIGINT, SIG_IGN);
	wait_pids(g_shell.pids, cmd_counts);
	set_signals();
	free(g_shell.pids);
}
