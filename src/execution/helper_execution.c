/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:34:37 by monajjar          #+#    #+#             */
/*   Updated: 2025/07/04 21:11:18 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"

int	getsize(t_cmd *lst)
{
	t_cmd	*ptr;
	int		i;

	if (!lst)
		return (0);
	i = 0;
	ptr = lst;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}

void	wait_pids(pid_t *pids, int cmd_counts)
{
	t_wait	w;

	w.i = 0;
	w.entred = 0;
	while (w.i < cmd_counts)
	{
		waitpid(pids[w.i], &w.status, 0);
		handle_sigint_output(&w, cmd_counts);
		if (w.i == cmd_counts - 1)
		{
			if (WIFEXITED(w.status))
				g_shell.last_exit_status = WEXITSTATUS(w.status);
			else if (WIFSIGNALED(w.status))
			{
				w.sig = WTERMSIG(w.status);
				g_shell.last_exit_status = 128 + w.sig;
				if (w.sig == SIGINT && w.entred == 0)
					write(1, "\n", 1);
				else if (w.sig == SIGQUIT)
					write(2, "Quit (core dumped)\n", 19);
			}
		}
		w.i++;
	}
}

pid_t	*allocate_pid(int size)
{
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * (size));
	if (!pids)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (pids);
}

int	close_and_update_pipe(t_cmd *cmd, int prev_fd, int pipefd[2])
{
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->is_pipe)
	{
		close(pipefd[1]);
		return (pipefd[0]);
	}
	return (-1);
}

int	check_null(char *str, char *msg)
{
	if (!str)
	{
		ft_putendl_fd(msg, 2);
		g_shell.last_exit_status = 1;
		return (1);
	}
	return (0);
}
