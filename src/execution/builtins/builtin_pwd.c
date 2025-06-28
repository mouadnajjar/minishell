/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:20 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/28 15:37:40 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"
#include "../../../includes/minishell.h"

int	get_pwd(char **env)
{
	char	*cwd;
	char	*pwd;

	(void)env;
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
		ft_putstr_fd("cd: error retrieving current directory:", 2);
		ft_putstr_fd(" getcwd: cannot access parent directories:", 2);
		ft_putendl_fd(" No such file or directory", 2);
		g_shell.last_exit_status = 1;
		return (1);
	}
	ft_putendl_fd(cwd, 1);
	free(cwd);
	g_shell.last_exit_status = 0;
	free_gc_memory();
	return (0);
}
