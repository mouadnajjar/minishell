/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/26 22:27:29 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

static int	copy_inside_quotes(const char *str, char *result, int i, int *j)
{
	char	quote;

	quote = str[i++];
	while (str[i] && str[i] != quote)
		result[(*j)++] = str[i++];
	if (str[i] == quote)
		i++;
	return (i);
}

char	*remove_quotes(const char *str)
{
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = gc_alloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTES || str[i] == DOUBLE_QUOTES)
			i = copy_inside_quotes(str, result, i, &j);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
