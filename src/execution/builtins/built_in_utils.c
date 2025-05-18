/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouad <mouad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:01:49 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/17 20:15:42 by mouad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/executor.h"

int	is_built_in(char *line)
{
	if (!line)
		return (0);
    if (ft_strncmp(line, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(line, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(line, "cd", 2) == 0)
		return (1);
	return (0);
}

char *ft_strjoin_3(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;
	char	*final;
	
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	final = ft_strjoin(tmp, s3);
	free (tmp);
	if (!final)
		return(NULL);
	return (final);
}

int	env_len(char **env)
{
	int	i;
	
	if (!env)
		return (0);
	i = 0;
	while (env && env[i])
	i++;
	return (i);
}

void	free_env_allocation(int i, char **env, char *var)
{
	while (--i >= 0)
		free(env[i]);
	free(env);
	if (var)
		free(var);
}

int	ft_realloc_env(char	***env, char *new_var)
{
	int		i;
	char	**new_env;

	if (!new_var)
		return (0);
	i = env_len(*env);
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		free(new_var);
		return (0);
	}
	i = -1;
	while ((*env)[++i])
	{
		new_env[i] = ft_strdup((*env)[i]);
		if (!new_env[i])
			return (free_env_allocation(i, new_env, new_var), 0);
	}
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free_2d_array(*env);
	*env = new_env;
	return (1);
}
