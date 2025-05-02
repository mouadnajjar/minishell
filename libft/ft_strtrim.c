/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:59:22 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/02 15:44:27 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_set(char s1, char const *set)
{
	size_t	j;

	j = 0;
	while (set[j])
	{
		if (s1 == set[j])
		{
			return (1);
		}
		j++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	end;
	size_t	start;
	char	*string;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && count_set(s1[start], set))
	{
		start++;
	}
	while (end > start && count_set(s1[end], set))
	{
		end--;
	}
	i = end - start + 1;
	string = (char *)malloc(i + 1);
	if (!string)
		return (NULL);
	ft_strlcpy(string, s1 + start, i + 1);
	return (string);
}
