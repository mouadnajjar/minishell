/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:20 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/17 16:25:03 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"
#include "../../../includes/minishell.h"

int	get_pwd(char **env)
{
	char	*cwd;
	char	*pwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putendl_fd(cwd, 1);
		free(cwd);
		g_shell.last_exit_status = 0;
		gc_free_all();
		free(g_shell.pids);
		return (0);
	}
	else
	{
		pwd = get_env_value(env, "PWD");
		if (pwd)
		{
			ft_putendl_fd(pwd, 1);
			g_shell.last_exit_status = 0;
			return (0);
		}
		ft_putendl_fd("minishell: pwd: ", 2);
		g_shell.last_exit_status = 1;
		return (1);
	}
}
