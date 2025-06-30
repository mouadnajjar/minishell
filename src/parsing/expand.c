/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/30 18:45:36 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

char	*get_var_name(const char *src, size_t i, size_t *out_len)
{
	size_t	len;
	char	*name;
	size_t	k;

	len = 0;
	while (src[i + len] && (ft_isalnum(src[i + len]) || src[i + len] == '_'))
		len++;
	name = gc_alloc(len + 1);
	k = 0;
	while (k < len)
	{
		name[k] = src[i + k];
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

void	handle_dollar_case(const char *src, size_t *i, char *dst, size_t *j)
{
	g_shell.ambg_name = NULL;
	g_shell.ambiguous_redirect = 0;
	(*i)++;
	if (src[*i] == '\0')
		append_dollar(dst, j);
	else if (src[*i] == '?')
	{
		expand_status(dst, j);
		(*i)++;
	}
	else if (ft_isdigit(src[*i]))
		(*i)++;
	else if (ft_isalnum(src[*i]) || src[*i] == '_')
		handle_variable_expansion(src, i, dst, j);
	else
		append_dollar(dst, j);
	if (ft_isdigit(src[1]) && src[2] == '\0')
	{
		g_shell.ambiguous_redirect = 1;
		g_shell.ambg_name = (char *)src + 1;
	}
}

char	*expand_value(const char *src, t_token *tok)
{
	char	*dst;

	size_t(j),
	(len), (i);
	len = get_expanded_length(src);
	dst = gc_alloc(len + 1);
	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '$')
		{
			handle_dollar_case(src, &i, dst, &j);
			if (tok)
				tok->from_expansion = 1;
		}
		else
		{
			if (tok)
				tok->from_expansion = 0;
			copy_char(dst, src, &i, &j);
		}
	}
	dst[j] = '\0';
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
