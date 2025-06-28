/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:52:32 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/28 16:24:42 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executor.h"

void	free_2d_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	free_gc_memory(void)
{
	gc_free_all();
	if (g_shell.pids)
		free(g_shell.pids);
}

void	set_and_free(void)
{
	g_shell.heredoc_sigint = 0;
	if (g_shell.pids)
		free(g_shell.pids);
}
