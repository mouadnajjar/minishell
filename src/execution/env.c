/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:07:22 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/02 14:19:04 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"


// has been changed to use gc_malloc

char **copy_env(char **envp)
{
    char **new_env;
    size_t i;

    i = 0;
    while (envp && envp[i])
        i++;
    new_env = malloc( (i + 1) * sizeof(char *));
    if (!new_env)
        return (NULL);
    i = 0;
    while (envp && envp[i])
    {
        new_env[i] = ft_strdup(envp[i]);
        if (!new_env[i])
            return (NULL);
        ft_strlcpy(new_env[i], envp[i], ft_strlen(envp[i]) + 1);
        i++;
    }
    new_env[i] = NULL;
    return (new_env);
}
