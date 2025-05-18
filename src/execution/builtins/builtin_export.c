/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:39:34 by monajjar             #+#    #+#             */
/*   Updated: 2025/05/17 19:39:35 by monajjar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/executor.h"

void    sorting_env(char    **env)
{
    int     i;
    int     j;
    char    *tmp;
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

char    **dup_2d(char   **env)
{
    int     i;
    char    **new_env;

    i = env_len(env);
    new_env = malloc(sizeof(char *) * (i + 1));
    if (!new_env)
        return (NULL);
    i = 0;
    while(env[i])
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

void    print_sorted_export(char **env)
{
    char    **copy;
    int     i;

    copy = dup_2d(env);
    sorting_env(env);
    i = 0;
    while(env[i])
    {
        
    }
}

int builtin_export(char **argv, char ***env)
{

}