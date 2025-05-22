/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:52:32 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/13 14:32:03 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_2d_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void    free_env(char **env)
{
    int i;

    i = 0;
    while (env[i])
	{
        free(env[i]);
		i++;
	}
    free(env);
}
