/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/28 15:47:00 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

static char	replace_opening_quote(char *input, size_t *i)
{
	char	quote;

	quote = input[*i];
	if (quote == '\'' || quote == '"')
	{
		if (quote == '"')
			input[*i] = DOUBLE_QUOTES;
		else
			input[*i] = SINGLE_QUOTES;
	}
	(*i)++;
	return (quote);
}

static char	process_closing_quote(char *input, size_t *i, char quote)
{
	if (input[*i] == quote)
	{
		if (quote == '"' || quote == '\'')
		{
			if (quote == '"')
				input[*i] = DOUBLE_QUOTES;
			else
				input[*i] = SINGLE_QUOTES;
			quote = input[*i];
		}
	}
	return (quote);
}

t_token	*extract_quoted(char *input, size_t *i)
{
	char	quote;
	size_t	start;
	size_t	len;
	char	*value;
	t_token	*token;

	quote = replace_opening_quote(input, i);
	start = *i;
	len = get_quoted_length(input, i, quote);
	quote = process_closing_quote(input, i, quote);
	if (input[*i] != quote)
	{
		print_parse_error(ERR_UNCLOSED_QUOTE, &quote);
		return (NULL);
	}
	value = alloc_quoted_value(input, start, len, quote);
	if (!value)
		return (NULL);
	token = create_quoted_token(value, start, *i, quote);
	(*i)++;
	return (token);
}

t_token	*extract_special(const char *input, size_t *i)
{
	size_t			start;
	char			*op;
	t_token_type	type;
	t_token			*token;

	start = *i;
	op = get_operator(input, i);
	if (!op)
		return (NULL);
	type = validate_and_get_type(op);
	if (type == TOKEN_INVALID)
		return (NULL);
	token = gc_alloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = op;
	token->type = type;
	token->can_expand = 0;
	token->start_index = start;
	token->end_index = *i - 1;
	token->from_expansion = 0;
	token->is_heredoc_delim = 0;
	return (token);
}

t_token	*extract_word(const char *input, size_t *i)
{
	size_t	start;
	size_t	len;

	start = *i;
	len = 0;
	while (!is_word_end(input[*i]))
	{
		(*i)++;
		len++;
	}
	if (len == 0)
		return (NULL);
	return (alloc_word_token(input, start, len));
}
