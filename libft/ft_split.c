/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:38:38 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/02 15:43:18 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_word(const char *str, char c)
{
	size_t	counter;
	size_t	j;

	counter = 0;
	j = 0;
	while (str[j])
	{
		while (str[j] && str[j] == c)
			j++;
		if (str[j])
			counter++;
		while (str[j] && str[j] != c)
			j++;
	}
	return (counter);
}

static int	free_split(char **result)
{
	size_t	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}

static char	**allocate_split(size_t nb_word)
{
	char	**split;

	split = (char **)malloc((nb_word + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	return (split);
}

static int	extract_words(char **split, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			split[j] = ft_substr(s, start, i - start);
			if (!split[j])
				return (0);
			j++;
		}
	}
	split[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t		nb_word;
	char		**split;

	if (!s)
		return (NULL);
	nb_word = count_word(s, c);
	split = allocate_split(nb_word);
	if (!split)
		return (NULL);
	if (!extract_words(split, s, c))
	{
		free_split(split);
		return (NULL);
	}
	return (split);
}
