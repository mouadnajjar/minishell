/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:21:41 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/22 15:44:02 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"
#include "../../../includes/minishell.h"

static int	find_env_index(char **env, const char *key)
{
	int	i;
	int	len;

	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len) && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	remove_env_and_shift(char ***env, int index)
{
	free((*env)[index]);
	while ((*env)[index])
	{
		(*env)[index] = (*env)[index + 1];
		index++;
	}
}

int	builtin_unset(char **argv, char ***env)
{
	int	i;
	int	inx;

	i = 1;
	while (argv[i])
	{
		if (ft_isalpha(argv[i][0]) || argv[i][0] == '_')
		{
			inx = find_env_index(*env, argv[i]);
			if (inx != -1)
				remove_env_and_shift(env, inx);
		}
		i++;
	}
	return (0);
}
