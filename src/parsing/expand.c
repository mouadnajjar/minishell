/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/19 18:13:08 by monajjar         ###   ########.fr       */
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
	size_t	len;
	char	*name;

	(*i)++;
	if (src[*i] == '\0')
		append_dollar(dst, j);
	else if (src[*i] == '?')
	{
		expand_status(dst, j);
		(*i)++;
	}
	else if (ft_isalnum(src[*i]) || src[*i] == '_')
	{
		name = get_var_name(src, *i, &len);
		append_var_value(name, dst, j);
		*i += len;
	}
	else
		append_dollar(dst, j);
}

char	*expand_value(const char *src, t_token *tok)
{
	char	*dst;
	size_t	len;
	size_t	i;
	size_t	j;

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
            	tok->from_expansion = 1; // Mark token as expanded
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
			expanded = expand_value(tok->value , tok);
			tok->value = gc_strdup(expanded);
			// printf("[expand_tokens] %s\n", tok->value); // 🟢 Debug line
		}
		tokens = tokens->next;
	}
}

// char	*expand_value(const char *src)
// {
// 	size_t final_len = get_expanded_length(src);
// 	char *result = gc_alloc(final_len + 1, &gc);
// 	size_t j = 0;

// 	size_t i = 0;
// 	while (src[i])
// 	{
// 		if (src[i] == '$')
// 		{
// 			i++;
// 			if (src[i] == '\0')
// 			{
// 				result[j++] = '$'; // case: lone $
// 				break ;
// 			}
// 			else if (src[i] == '?')
// 			{
// 				char *num = ft_itoa(g_shell.last_exit_status);
// 				gc_add(num, &gc);
// 				size_t k = 0;
// 				while (num[k])
// 					result[j++] = num[k++];
// 			}
// 			else if (ft_isalnum(src[i]) || src[i] == '_')
// 			{
// 				size_t var_len = 0;
// 				while (src[i + var_len] && (ft_isalnum(src[i + var_len])
// 						|| src[i + var_len] == '_'))
// 					var_len++;
// 				char *name = gc_alloc(var_len + 1, &gc);
// 				size_t k = 0;
// 				while (k < var_len)
// 				{
// 					name[k] = src[i + k];
// 					k++;
// 				}
// 				name[k] = '\0';
// 				char *val = get_env_var(name);
// 				if (val)
// 				{
// 					k = 0;
// 					while (val[k])
// 						result[j++] = val[k++];
// 				}
// 				i += var_len - 1;
// 			}
// 			else
// 			{
// 				// Not a valid variable name, treat as literal $
// 				result[j++] = '$';
// 				i--; // reprocess current char normally
// 			}
// 		}
// 		else
// 		{
// 			result[j++] = src[i];
// 		}
// 		i++;
// 	}
// 	result[j] = '\0';
// 	// printf("[expand_value] %s => %s\n", src, result); // 🟢 Debug line
// 	return (result);
// }
