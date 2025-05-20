/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:41:48 by monajjar          #+#    #+#             */
/*   Updated: 2024/11/14 10:51:27 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	adresse(unsigned long n)
{
	int	result;

	result = 0;
	if (n == 0)
	{
		ft_putstr("0x0");
		return (3);
	}
	ft_putstr("0x");
	result += ft_hexa(n, 'x') + 2;
	return (result);
}
