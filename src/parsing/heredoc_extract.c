/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_extract.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/30 16:43:05 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"

static int	parse_quoted_section(char *input, size_t *curr, char *quote_out)
{
	char (quote), (original_quote);
	if (input[*curr] == '\'')
	{
		quote = SINGLE_QUOTES;
		original_quote = '\'';
	}
	else if (input[*curr] == '"')
	{
		quote = DOUBLE_QUOTES;
		original_quote = '"';
	}
	else
		return (0);
	input[*curr] = quote;
	(*curr)++;
	while (input[*curr] && input[*curr] != original_quote)
		(*curr)++;
	if (input[*curr] != original_quote)
		return (print_parse_error(ERR_UNCLOSED_QUOTE, &original_quote), -1);
	input[*curr] = quote;
	*quote_out = original_quote;
	return (1);
}

size_t	skip_word_and_quotes(char *input, size_t start, char *last_quote,
		int *has_quotes)
{
	size_t	curr;
	int		result;

	curr = start;
	while (input[curr] && !ft_isspace(input[curr]))
	{
		if (input[curr] == '\'' || input[curr] == '"')
		{
			result = parse_quoted_section(input, &curr, last_quote);
			if (result == -1)
				return ((size_t) - 1);
			*has_quotes = 1;
		}
		if (input[curr])
			curr++;
	}
	return (curr);
}

t_token	*build_heredoc_token(char *input, size_t start, size_t curr,
		char quote_for_token)
{
	size_t	len;
	char	*value;
	t_token	*token;

	len = curr - start;
	value = alloc_quoted_value_heredoc(input, start, len);
	if (!value)
		return (NULL);
	token = create_quoted_token_heredoc(value, start, curr - 1,
			quote_for_token);
	return (token);
}

t_token	*extract_quoted_heredoc(char *input, size_t *i)
{
	t_heredoc_extract	ctx;

	ctx.start = *i;
	ctx.last_quote = 0;
	ctx.has_quotes = 0;
	ctx.curr = skip_word_and_quotes(input, ctx.start, &ctx.last_quote,
			&ctx.has_quotes);
	if (ctx.curr == (size_t)-1)
		return (NULL);
	ctx.quote_for_token = 0;
	if (ctx.has_quotes)
		ctx.quote_for_token = ctx.last_quote;
	ctx.token = build_heredoc_token(input, ctx.start, ctx.curr,
			ctx.quote_for_token);
	if (!ctx.token)
		return (NULL);
	*i = ctx.curr;
	return (ctx.token);
}

t_list	*extract_heredoc_delimiter(char *input, size_t *i)
{
	t_token	*next;
	t_list	*node;

	next = NULL;
	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
	if (is_quoted_origin(input + *i))
		next = extract_quoted_heredoc(input, i);
	else if (!is_special(input + *i) && input[*i] != '\0')
		next = extract_word(input, i);
	if (!next)
		return (NULL);
	next->is_heredoc_delim = 1;
	node = ft_lstnew(next);
	gc_add(node);
	return (node);
}
