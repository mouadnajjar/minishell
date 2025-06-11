/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:36:54 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/02 11:56:00 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"
#include "../../../includes/minishell.h"

int	builtin_env(char **argv, char **env)
{
	int	i;

	i = 0;
	if (argv[1])
	{
		ft_putendl_fd("minishell: env: too many arguments", 2);
		g_exit_status = 1;
		return (1);
	}
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			ft_putendl_fd(env[i], 1);
		i++;
	}
	return (0);
}
