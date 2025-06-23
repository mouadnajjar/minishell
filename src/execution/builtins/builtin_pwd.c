/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:20 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/23 18:22:19 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"
#include "../../../includes/minishell.h"

int	get_pwd(char **env)
{
	char	*cwd;
	char	*pwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		pwd = get_env_value(env, "PWD");
		if (pwd)
		{
			ft_putendl_fd(pwd, 1);
			g_shell.last_exit_status = 0;
			return (0);
		}
		ft_putendl_fd("minishell: pwd: error retrieving current directory", 2);
		g_shell.last_exit_status = 1;
		return (1);
	}
	ft_putendl_fd(cwd, 1);
	free(cwd);
	g_shell.last_exit_status = 0;
	free_gc_memory();
	return (0);
}
