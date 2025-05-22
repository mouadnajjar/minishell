/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:34:37 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/09 16:11:27 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"
#include"../../includes/executor.h"

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

void    wait_pids(pid_t *pids, int cmd_counts)
{
    int i;
    int	status;
    i = 0;
    while (i < cmd_counts)
    {
        waitpid(pids[i], &status, 0);
        i++;
    }
}

pid_t *allocate_pid(int size)
{
    pid_t *pids;
    
    pids = malloc (sizeof(pid_t) * (size));
	if (!pids)
	{
		perror("malloc");
		exit (EXIT_FAILURE);
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
