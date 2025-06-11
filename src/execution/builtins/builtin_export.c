/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:35:27 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/11 16:35:29 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"
#include "../../../includes/minishell.h"

void	sorting_env(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strncmp(env[i], env[j], ft_strlen(env[i] + 1)) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**dup_2d(char **env)
{
	int		i;
	char	**new_env;

	i = env_len(env);
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			free_env_allocation(i, new_env, NULL);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	print_sorted_env(char **env)
{
	char	**copy;
	char	*equal_start;
	int		i;

	copy = dup_2d(env);
	sorting_env(copy);
	i = 0;
	while (copy[i])
	{
		equal_start = ft_strchr(copy[i], '=');
		if (equal_start)
		{
			*equal_start = '\0';
			ft_printf("declare -x %s=\"%s\"\n", copy[i], equal_start + 1);
			*equal_start = '=';
		}
		else
			ft_printf("declare -x %s\n", copy[i]);
		i++;
	}
	free_2d_array(copy);
}

int	is_valid_identifier(char *str)
{
	int		i;
	char	*key;
	char	*eq;

	i = 0;
	eq = ft_strchr(str, '=');
	if (eq && eq > str && *(eq - 1) == '+')
		key = ft_substr(str, 0, (eq - str) - 1);
	else if (eq)
		key = ft_substr(str, 0, (eq - str));
	else
		key = ft_strdup(str);
	if (!key)
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (free(key), 0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (free(key), 0);
		i++;
	}
	free(key);
	return (1);
}

int	builtin_export(char **argv, char ***env)
{
	int	i;
	int	status;

	if (!argv[1])
	{
		print_sorted_env(*env);
		return (0);
	}
	i = 1;
	status = 0;
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			print_export_error(argv[i]);
			status = 1;
		}
		else
			handle_export_assigment(argv[i], env);
		i++;
	}
	return (status);
}
