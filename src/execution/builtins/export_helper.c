/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:17:40 by monajjar          #+#    #+#             */
/*   Updated: 2025/07/08 18:09:23 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"
#include "../../../includes/minishell.h"
#include "../../../includes/parser.h"

void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

void	handle_plus_equal(char *arg, char ***env)
{
	char	*key;
	char	*append_value;
	char	*old_value;
	char	*new_value;
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (!eq || eq == arg)
		return ;
	key = ft_substr(arg, 0, (eq - arg) - 1);
	if (!key)
		return ;
	append_value = ft_strdup(eq + 1);
	if (!append_value)
		return (free(key));
	old_value = get_env_value(*env, key);
	if (old_value)
		new_value = ft_strjoin(old_value, append_value);
	else
		new_value = ft_strdup(append_value);
	if (new_value)
		update_env(env, key, new_value);
	free(append_value);
	free(key);
	free(new_value);
}

static void	handle_existing_var(char ***env, char *key, char *value)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strcmp((*env)[i], key) == 0)
		{
			free((*env)[i]);
			(*env)[i] = ft_strjoin_3(key, "=", value);
			free(key);
			free(value);
			return ;
		}
		i++;
	}
	update_env(env, key, value);
	free(key);
	free(value);
}

void	handle_export_assigment(char *arg, char ***env)
{
	char	*eq;
	char	*key;
	char	*value;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		if (ft_strncmp(eq - 1, "+", 1) == 0)
		{
			handle_plus_equal(arg, env);
			return ;
		}
		key = ft_substr(arg, 0, eq - arg);
		value = ft_strdup(eq + 1);
		handle_existing_var(env, key, value);
	}
	else
	{
		if (!get_env_value(*env, arg))
			ft_realloc_env(env, ft_strdup(arg));
	}
}
