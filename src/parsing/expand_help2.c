/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_help2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/07/04 18:18:11 by ahlahfid         ###   ########.fr       */
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

void	handle_variable_expansion(const char *src, t_inc *inc, char *dst,
		t_token *tok)
{
	size_t	len;
	char	*name;

	name = get_var_name(src, inc, &len);
	append_var_value(name, dst, &inc->j);
	if (tok && (dst[0] == '\0' || gc_count_word(dst) > 1) && !tok->quoted_2)
	{
		tok->ambiguous_redirect = 1;
		tok->ambg_name = gc_strdup((char *)src + 1);
	}
	inc->i += len;
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
