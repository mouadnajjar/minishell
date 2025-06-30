/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_help2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/29 13:50:07 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

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

void	handle_variable_expansion(const char *src, size_t *i, char *dst,
		size_t *j)
{
	size_t	len;
	char	*name;

	name = get_var_name(src, *i, &len);
	append_var_value(name, dst, j);
	if (dst[0] == '\0' || gc_count_word(dst) > 1)
	{
		g_shell.ambg_name = name;
		g_shell.ambiguous_redirect = 1;
	}
	*i += len;
}

size_t	get_exit_status_len(void)
{
	char	*num;
	size_t	len;

	num = ft_itoa(g_shell.last_exit_status);
	len = ft_strlen(num);
	gc_add(num);
	return (len);
}
