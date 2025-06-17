/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/17 11:37:18 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

t_token	*extract_quoted( char *input, size_t *i)
{
	char	quote;
	size_t	len;
	char	*value;
	t_token	*token;
	size_t	start;

	quote = input[*i];
	if (quote != '\'' || quote != '"')
	{
		if (quote == '"')
			input[*i] = DOUBLE_QUOTES;
		else
			input[*i] = SINGLE_QUOTES;
	}
	start = ++(*i);
	len = get_quoted_length(input, i, quote);
	if (input[*i] == quote)
	{
		if (quote != '\'' || quote != '"')
		{
			if (quote == '"')
			input[*i] = DOUBLE_QUOTES;
			else
			input[*i] = SINGLE_QUOTES;
			quote = input[*i];
		}
	}
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
// t_token	*extract_quoted(const char *input, size_t *i)
// {
// 	char	quote;
// 	size_t	start;
// 	size_t	len;
// 	char	*value;
// 	t_token	*token;

// 	len = 0;
// 	quote = input[*i]; // Either ' or "
// 	start = ++(*i);    // Move past the opening quote
// 	while (input[*i] && input[*i] != quote)
// 	{
// 		len++;
// 		(*i)++;
// 	}
// 	if (input[*i] != quote)
// 	{
// 		print_parse_error(ERR_UNCLOSED_QUOTE, &quote);
// 		return (NULL);
// 	}
// 	value = gc_alloc(len + 3, &gc); // +2 for quotes, +1 for '\0'
// 	if (!value)
// 		return (NULL);
// 	value[0] = quote;
// 	ft_strlcpy(value + 1, input + start, len + 1);
// 	value[len + 1] = quote;
// 	value[len + 2] = '\0';
// 	token = gc_alloc(sizeof(t_token), &gc);
// 	if (!token)
// 		return (NULL);
// 	token->value = value;
// 	token->type = TOKEN_WORD;
// 	token->can_expand = (quote == '"'); // allow expansion for double quote
// 	token->start_index = start; // ← full `'abc'`
// 	token->end_index = *i;
// 	(*i)++; // Skip closing quote
// 	return (token);
// }

// t_token	*extract_special(const char *input, size_t *i)
// {
// 	size_t			start;
// 	t_token			*token;
// 	char			*op;
// 	t_token_type	type;

// 	start = *i;
// 	op = get_operator(input, i);
// 	if (!op)
// 		return (NULL);
// 	if (!is_valid_redirection(op))
// 	{
// 		print_parse_error(ERR_UNEXPECTED_TOKEN, op);
// 		return (NULL);
// 	}
// 	type = get_operator_type(op);
// 	if (type == TOKEN_INVALID)
// 		return (NULL);
// 	token = gc_alloc(sizeof(t_token), &gc);
// 	if (!token)
// 		return (NULL);
// 	token->value = op;
// 	token->type = type;
// 	// printf("token->type: %d\n", token->type);
// 	token->can_expand = 0;
// 	token->start_index = start;
// 	token->end_index = *i - 1;
// 	return (token);
// }

// t_token	*extract_word(const char *input, size_t *i)
// {
// 	size_t	start;
// 	size_t	len;
// 	t_token	*token;
// 	char	*word;

// 	start = *i;
// 	len = 0;
// 	while (!is_word_end(input[*i]))
// 	{
// 		(*i)++;
// 		len++;
// 	}
// 	if (len == 0)
// 		return (NULL);
// 	word = gc_alloc(len + 1, &gc);
// 	if (!word)
// 		return (NULL);
// 	ft_strlcpy(word, input + start, len + 1);
// 	token = gc_alloc(sizeof(t_token), &gc);
// 	if (!token)
// 		return (NULL);
// 	token->value = word;
// 	token->type = TOKEN_WORD;
// 	token->can_expand = 1;
// 	token->start_index = start; // ← Track start
// 	token->end_index = *i - 1;  // ← Track end
// 	return (token);
// }
