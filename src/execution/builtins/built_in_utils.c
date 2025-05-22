/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:01:49 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/10 14:48:45 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/executor.h"

int	is_built_in(char *line)
{
	if (!line)
		return (0);
    if (ft_strncmp(line, "echo", 5) == 0)
		return (1);
	return (0);
}

