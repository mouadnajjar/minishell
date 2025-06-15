/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexaprint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:55:00 by monajjar          #+#    #+#             */
/*   Updated: 2024/11/14 14:56:26 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexa(unsigned long n, char c)
{
	int		len;
	char	*b16;

	len = 0;
	if (c == 'X')
		b16 = "0123456789ABCDEF";
	else if (c == 'x')
		b16 = "0123456789abcdef";
	if (n < 16)
	{
		len += ft_putchar(b16[n]);
		return (len);
	}
	else
	{
		len += ft_hexa(n / 16, c);
		len += ft_putchar(b16[n % 16]);
	}
	return (len);
}
