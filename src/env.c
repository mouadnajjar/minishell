/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:07:22 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/02 16:49:55 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executor.h"

char    **copy_env(char **envp)
{
    char    **new_env;
    size_t     i;

    i = 0;
    while (envp[i])
        i++;
    new_env = malloc((i + 1) * sizeof(char *));
    if (!new_env)
        return (NULL);
    i = 0;
    while(envp[i])
    {
        new_env[i] = ft_strdup(envp[i]);
        i++;
    }
    new_env[i] = NULL;
    return (new_env);
}

void    free_env(char **env)
{
    int i;
    
    i = 0;
    while (env[i])
        free(env[i]);
    free(env);
}
