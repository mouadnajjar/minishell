/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/29 11:21:56 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

static char	**gc_allocate_split(size_t nb_word)
{
	char	**split;

	split = (char **)gc_alloc((nb_word + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	return (split);
}

size_t	gc_count_word(const char *str)
{
	size_t	counter;
	size_t	j;

	counter = 0;
	j = 0;
	while (str[j])
	{
		while (str[j] && ft_isspace(str[j]))
			j++;
		if (str[j])
			counter++;
		while (str[j] && !ft_isspace(str[j]))
			j++;
	}
	return (counter);
}

static int	gc_extract_words(char **split, const char *s)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i])
		{
			start = i;
			while (s[i] && !ft_isspace(s[i]))
				i++;
			split[j] = gc_substr(s, start, i - start);
			if (!split[j])
				return (0);
			j++;
		}
	}
	split[j] = NULL;
	return (1);
}

char	**gc_split(char const *s)
{
	size_t	nb_word;
	char	**split;

	if (!s)
		return (NULL);
	nb_word = gc_count_word(s);
	split = gc_allocate_split(nb_word);
	if (!split)
		return (NULL);
	if (!gc_extract_words(split, s))
		return (NULL);
	return (split);
}
