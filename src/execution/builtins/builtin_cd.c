/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:03:21 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/13 16:52:28 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"
#include "../../../includes/minishell.h"

char	*get_env_value(char **env, const char *key)
{
	int	i;
	int	len;

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

	if (check_arguments_cd(argv))
		return (1);
	oldpath = getcwd(NULL, 0);
	if (!oldpath)
	{
		oldpath = ft_strdup(get_env_value(*env, "PWD"));
		if (!oldpath)
		{
			ft_putendl_fd("minishell: cd: failed to retrieve PWD", 2);
			return (1);
		}
	}
	path = get_cd_path(argv, env);
	if (change_directory(path))
	{
		free(oldpath);
		return (1);
	}
	update_cd_env(env, oldpath);
	free(oldpath);
	return (0);
}
