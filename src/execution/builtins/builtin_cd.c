/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:03:21 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/13 18:53:20 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/executor.h"

char *get_env_value(char **env, const char *key)
{
    int i;
    int len;
    
    len = ft_strlen(key);
    i = 0;
    while (env[i])
    {
        if (!ft_strncmp(env[i], key, len) && env[i][len] == '=')
            return (env[i] + len + 1);
        i++;
    }
    return (NULL);
}

void	update_env(char ***env, char *key, char *value)
{
	char	*new_var;
	int		i;
	int		keylen;

	keylen = ft_strlen(key);
	new_var = ft_strjoin_3(key, "=", value);
	if (!new_var)
		return ;
	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], key, keylen) && (*env)[i][keylen] == '=')
		{
			free((*env)[i]);
			(*env)[i] = new_var;
			return ;
		}
		i++;
	}
	if (!ft_realloc_env(env, new_var))
		return ;
}


int	builtin_cd(char **argv, char ***env)
{
	char	*path;
	char	*oldpath;
	char	*newpwd;

	oldpath = getcwd(NULL, 0);
	if (!oldpath)
	{
		perror("minishell: cd");
		return (1);
	}
	if (!argv[1])
		path = get_env_value(*env, "HOME");
	else if (ft_strncmp(argv[1], "-", 1) == 0)
	{
		path = get_env_value(*env, "OLDPWD");
		if (path)
			ft_putendl_fd(path, 1);
	}
	else
		path = argv[1];

	if (!path || chdir(path) != 0)
	{
		perror("minishell: cd");
		free(oldpath);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	if (newpwd)
	{
		update_env(env, "OLDPWD", oldpath);
		update_env(env, "PWD", newpwd);
		free(newpwd);
	}
	free(oldpath);
	return (0);
}

