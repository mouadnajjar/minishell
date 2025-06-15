/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:14:32 by monajjar          #+#    #+#             */
/*   Updated: 2024/11/14 10:49:55 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

# define FT_PRINTF_H

int	ft_printf(const char *fstring, ...);
int	ft_putstr(char *s);
int	ft_putchar(char c);
int	ft_putint(int n);
int	ft_putunsigned(unsigned int n);
int	ft_hexa(unsigned long n, char c);
int	adresse(size_t n);

#endif