/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:39:36 by monajjar          #+#    #+#             */
/*   Updated: 2024/11/13 12:40:09 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_countlen(unsigned int i)
{
	unsigned int	c;

	c = 0;
	if (i == 0)
		c++;
	while (i != 0)
	{
		c++;
		i = i / 10;
	}
	return (c);
}

int	ft_putunsigned(unsigned int n)
{
	int	count;

	count = ft_countlen(n);
	if (n > 9)
	{
		ft_putunsigned(n / 10);
		ft_putchar((n % 10) + 48);
	}
	else
		ft_putchar(n + 48);
	return (count);
}
