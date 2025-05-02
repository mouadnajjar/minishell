/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:21:40 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/02 15:41:46 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*p;
	size_t	box;

	if (nmemb == 0 || size == 0)
	{
		p = malloc (0);
		if (!p)
			return (NULL);
		return (p);
	}
	if (nmemb == SIZE_MAX || size == SIZE_MAX || nmemb > SIZE_MAX / size)
		return (NULL);
	box = nmemb * size;
	p = malloc(box);
	if (!p)
		return (NULL);
	ft_memset(p, 0, box);
	return (p);
}
