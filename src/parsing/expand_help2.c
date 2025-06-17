/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_help2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/17 11:38:42 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../includes/minishell.h"

void	copy_char(char *dst, const char *src, size_t *i, size_t *j)
{
	dst[(*j)++] = src[(*i)++];
}

void	append_dollar(char *dst, size_t *j)
{
	dst[(*j)++] = '$';
}

void	expand_status(char *dst, size_t *j)
{
	char	*num;
	size_t	k;

	num = ft_itoa(g_shell.last_exit_status);
	gc_add(num);
	k = 0;
	while (num[k])
		dst[(*j)++] = num[k++];
}
