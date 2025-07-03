/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/07/03 15:46:37 by ahlahfid         ###   ########.fr       */
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

char	*remove_quotes(const char *str, t_token *tok)
{
	char	*result;

	int (i), (j);
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
		{
			if (tok && str[i] == DOUBLE_QUOTES)
				tok->quoted_2 = 1;
			else if (tok)
				tok->quoted_2 = 0;
			i = copy_inside_quotes(str, result, i, &j);
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
