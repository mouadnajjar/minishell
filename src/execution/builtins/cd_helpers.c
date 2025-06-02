/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:08:38 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/02 11:53:36 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/executor.h"

int check_arguments_cd(char **argv)
{
    if (argv[1] && argv[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

char    *get_cd_path(char **argv, char ***env)
{
    char *oldpwd;
    
    if (!argv[1] || (argv[1][0] == '~' && argv[1][1] == '\0')
		|| (ft_strncmp(argv[1], "--", 3) == 0))
		return (get_env_value(*env, "HOME"));
	else if (ft_strncmp(argv[1], "-", 2) == 0)
	{
		oldpwd = get_env_value(*env, "OLDPWD");
		if (!oldpwd)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			return (NULL);
		}
		ft_putendl_fd(oldpwd, 1);
		return (oldpwd);
	}
	else
		return (argv[1]);
}

int change_directory(char *path)
{
	if (!path || chdir(path) != 0)
	{
		perror("minishell: cd");
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

void	update_cd_env(char ***env, char *oldpwd)
{
	char *newpwd;
    
    newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return ;
	if (get_env_value(*env, "PWD"))
		update_env(env, "PWD", newpwd);
	if (get_env_value(*env, "OLDPWD"))
		update_env(env, "OLDPWD", oldpwd);
	
	free(newpwd);
}
