/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:36:54 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/22 16:43:27 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/executor.h"

int builtin_env(char **argv, char **env)
{
    int i;

    i = 0;
    if (argv[1])
    {
        ft_putendl_fd("minishell: env: too many arguments", 2);
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
