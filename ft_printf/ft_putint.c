/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:04:20 by monajjar          #+#    #+#             */
/*   Updated: 2024/11/14 10:59:44 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_countlen(int i)
{
	unsigned int	c;

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

int	ft_putint(int n)
{
	int	count;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	count = ft_countlen(n);
	if (n < 0)
	{
		ft_putchar('-');
		ft_putint(-n);
	}
	else if (n > 9)
	{
		ft_putint(n / 10);
		ft_putchar((n % 10) + 48);
	}
	else
		ft_putchar(n + 48);
	return (count);
}
