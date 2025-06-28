/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:08:38 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/28 16:26:08 by monajjar         ###   ########.fr       */
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
	if (!path)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		g_shell.last_exit_status = 1;
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		g_shell.last_exit_status = 1;
		return (1);
	}
	return (0);
}

static	void	handle_deleted_dir(char ***env, char *oldpwd, char *pwd_value)
{
	char	*fallback;

	if (get_env_value(*env, "OLDPWD"))
		update_env(env, "OLDPWD", oldpwd);
	else
		ft_realloc_env(env, ft_strjoin_3("OLDPWD", "=", oldpwd));
	fallback = ft_strjoin(pwd_value, "/..");
	if (fallback)
	{
		update_env(env, "PWD", fallback);
		free(fallback);
	}
	ft_putstr_fd("cd: error retrieving current directory:", 2);
	ft_putstr_fd(" getcwd: cannot access parent directories:", 2);
	ft_putendl_fd(" No such file or directory", 2);
}

void	update_cd_env(char ***env, char *oldpwd)
{
	char	*newpwd;
	char	*pwd_value;

	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		pwd_value = get_env_value(*env, "PWD");
		if (pwd_value)
			handle_deleted_dir(env, oldpwd, pwd_value);
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
