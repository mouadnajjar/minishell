/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:34:37 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/02 14:13:04 by monajjar         ###   ########.fr       */
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
	int	i;
	int	status;
	int	sig;

	i = 0;
	while (i < cmd_counts)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_counts - 1)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				g_exit_status = 128 + sig;
				if (sig == SIGINT)
					write(1, "\n", 1);
				else if (sig == SIGQUIT)
					write(1, "Quit (core dumped)\n", 19);
			}
		}
		i++;
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
		g_exit_status = 1;
		return (1);
	}
	return (0);
}
