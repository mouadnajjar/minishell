/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:08:38 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/24 15:58:29 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"
#include "../../../includes/minishell.h"

int	check_arguments_cd(char **argv)
{
	if (argv[1] && argv[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		g_shell.last_exit_status = 1;
		return (1);
	}
	return (0);
}

char	*get_cd_path(char **argv, char ***env)
{
	if (!argv[1])
		return (get_env_value(*env, "HOME"));
	else
		return (argv[1]);
}

int	change_directory(char *path)
{
	char	*current;

	if (!path)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		g_shell.last_exit_status = 1;
		return (1);
	}
	current = getcwd(NULL, 0);
	if (!current && path[0] == '.' && path[1] == '.')
	{
		ft_putendl_fd("cd: error retrieving current directory:", 2);
		ft_putstr_fd(" getcwd: cannot access parent directories:", 2);
		ft_putendl_fd(" No such file or directory", 2);
		g_shell.last_exit_status = 1;
		return (1);
	}
	free(current);
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		g_shell.last_exit_status = 1;
		return (1);
	}
	return (0);
}

void	update_cd_env(char ***env, char *oldpwd)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		ft_putendl_fd("cd: error retrieving current directory:", 2);
		ft_putstr_fd(" getcwd: cannot access parent directories:", 2);
		ft_putendl_fd(" No such file or directory", 2);
		if (get_env_value(*env, "OLDPWD"))
			update_env(env, "OLDPWD", oldpwd);
		else
			ft_realloc_env(env, ft_strjoin_3("OLDPWD", "=", oldpwd));
		return ;
	}
	if (get_env_value(*env, "PWD"))
		update_env(env, "PWD", newpwd);
	if (get_env_value(*env, "OLDPWD"))
		update_env(env, "OLDPWD", oldpwd);
	else
		ft_realloc_env(env, ft_strjoin_3("OLDPWD", "=", oldpwd));
	free(newpwd);
}
