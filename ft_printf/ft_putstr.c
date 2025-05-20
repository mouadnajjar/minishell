/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:34:53 by monajjar          #+#    #+#             */
/*   Updated: 2024/11/13 12:39:16 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_strlen(const	char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_putstr(char *s)
{
	int	j;

	j = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s && s[j])
	{
		ft_putchar(s[j]);
		j++;
	}
	return (ft_strlen(s));
}
