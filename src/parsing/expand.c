/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/07/03 15:45:13 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

char	*get_var_name(const char *src, t_inc *inc, size_t *out_len)
{
	size_t	len;
	char	*name;
	size_t	k;

	len = 0;
	while (src[inc->i + len] && (ft_isalnum(src[inc->i + len]) || src[inc->i
				+ len] == '_'))
		len++;
	name = gc_alloc(len + 1);
	k = 0;
	while (k < len)
	{
		name[k] = src[inc->i + k];
		k++;
	}
	name[len] = '\0';
	*out_len = len;
	return (name);
}

void	append_var_value(const char *name, char *dst, size_t *j)
{
	char	*val;
	size_t	k;

	val = get_env_var(name);
	if (val)
	{
		k = 0;
		while (val[k])
			dst[(*j)++] = val[k++];
	}
}

void	handle_dollar_case(const char *src, t_inc *inc, char *dst, t_token *tok)
{
	tok->ambiguous_redirect = 0;
	tok->ambg_name = NULL;
	(inc->i)++;
	if (src[inc->i] == '\0')
		append_dollar(dst, &inc->j);
	else if (src[inc->i] == '?')
	{
		expand_status(dst, &inc->j);
		(inc->i)++;
	}
	else if (ft_isdigit(src[inc->i]))
		(inc->i)++;
	else if (ft_isalnum(src[inc->i]) || src[inc->i] == '_')
		handle_variable_expansion(src, inc, dst, tok);
	else
		append_dollar(dst, &inc->j);
	if (ft_isdigit(src[1]) && src[2] == '\0')
	{
		tok->ambiguous_redirect = 1;
		tok->ambg_name = gc_strdup((char *)src + 1);
	}
}

char	*expand_value(const char *src, t_token *tok)
{
	char	*dst;
	t_inc	inc;
	size_t	len;

	len = get_expanded_length(src);
	dst = gc_alloc(len + 1);
	inc.i = 0;
	inc.j = 0;
	while (src[inc.i])
	{
		if (src[inc.i] == '$')
		{
			handle_dollar_case(src, &inc, dst, tok);
			if (tok)
				tok->from_expansion = 1;
		}
		else
		{
			if (tok)
				tok->from_expansion = 0;
			copy_char(dst, src, &inc.i, &inc.j);
		}
	}
	dst[inc.j] = '\0';
	return (dst);
}

void	expand_tokens(t_list *tokens)
{
	t_token	*tok;
	char	*expanded;

	while (tokens)
	{
		tok = (t_token *)tokens->content;
		if (tok->type == TOKEN_WORD && tok->can_expand
			&& !tok->is_heredoc_delim)
		{
			expanded = expand_value(tok->value, tok);
			tok->value = gc_strdup(expanded);
		}
		tokens = tokens->next;
	}
}
