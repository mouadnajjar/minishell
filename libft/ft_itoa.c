/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:45:19 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/02 15:42:03 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_countlen(long i)
{
	int	c;

	c = 0;
	if (i < 0)
	{
		i = -i;
		c = 1;
	}
	if (i == 0)
		c++;
	while (i > 0)
	{
		c++;
		i = i / 10;
	}
	return (c);
}

char	*ft_itoa(int nb)
{
	int		i;
	char	*string;
	long	n;

	n = nb;
	i = ft_countlen(n);
	string = (char *)malloc(i + 1);
	if (!string)
		return (NULL);
	if (n == 0)
		string[0] = '0';
	string[i] = '\0';
	i = i - 1;
	if (n < 0)
	{
		n = -n;
		string[0] = '-';
	}
	while (n > 0)
	{
		string[i--] = (n % 10) + 48;
		n /= 10;
	}
	return (string);
}
