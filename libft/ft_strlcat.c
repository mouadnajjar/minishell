/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:21:50 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/11 15:20:04 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	d;
	size_t	s;

	s = ft_strlen(src);
	if (size == 0 && !dst)
		return (s);
	d = ft_strlen(dst);
	if (d >= size)
		return (size + s);
	j = d;
	i = 0;
	while (src[i] && i < size - d - 1)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (d + s);
}
