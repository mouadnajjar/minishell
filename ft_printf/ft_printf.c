/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:17:13 by monajjar          #+#    #+#             */
/*   Updated: 2024/11/15 17:45:04 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_format(const char c, va_list list)
{
	int	len;

	len = 0;
	if (c == 'd' || c == 'i')
		len += ft_putint(va_arg(list, int));
	else if (c == 'c')
		len += ft_putchar(va_arg(list, int));
	else if (c == 's')
		len += ft_putstr(va_arg(list, char *));
	else if (c == 'u')
		len += ft_putunsigned(va_arg(list, unsigned int));
	else if (c == '%')
		len += ft_putchar('%');
	else if (c == 'X' || c == 'x')
		len += ft_hexa(va_arg(list, unsigned int), c);
	else if (c == 'p')
		len += adresse((unsigned long)va_arg(list, void *));
	else
		len += ft_putchar(c);
	return (len);
}

int	ft_printf(const char *fstring, ...)
{
	va_list	list;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!fstring || write(1, 0, 0) == -1)
		return (-1);
	va_start(list, fstring);
	while (fstring[i] && count != -1)
	{
		if (fstring[i] == '%')
		{
			if (fstring[i + 1] == '\0')
				count = -1;
			else
				count += ft_format(fstring[i + 1], list);
			i++;
		}
		else
			count += write(1, &fstring[i], 1);
		i++;
	}
	va_end(list);
	return (count);
}
/*
 #include <stdio.h>
int main ()
{
	unsigned int la = 55;
	
	int x = printf("%d %", la);
	printf("\ncount of printf ==> %d\n", x);
	puts("");
	x = ft_printf("%d%", la);
	printf("\ncount of ft_printf ==> %d\n", x);
}
*/
