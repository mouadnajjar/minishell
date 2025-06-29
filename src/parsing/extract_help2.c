/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_help2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/28 18:36:35 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

t_token	*alloc_word_token(const char *input, size_t start, size_t len)
{
	char	*word;
	t_token	*token;

	word = gc_alloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, input + start, len + 1);
	token = gc_alloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = word;
	token->type = TOKEN_WORD;
	token->can_expand = 1;
	token->is_heredoc_delim = 0;
	token->start_index = start;
	token->end_index = start + len - 1;
	token->from_expansion = 0;
	return (token);
}

t_token_type	validate_and_get_type(char *op)
{
	if (!is_valid_redirection(op))
	{
		print_parse_error(ERR_UNEXPECTED_TOKEN, op);
		printf("here\n");
		return (TOKEN_INVALID);
	}
	return (get_operator_type(op));
}

size_t	get_quoted_length(const char *input, size_t *i, char quote)
{
	size_t	len;

	len = 0;
	while (input[*i] && input[*i] != quote)
	{
		len++;
		(*i)++;
	}
	return (len);
}

char	*alloc_quoted_value(const char *input, size_t start, size_t len,
		char quote)
{
	char	*value;

	value = gc_alloc(len + 3);
	if (!value)
		return (NULL);
	value[0] = quote;
	ft_strlcpy(value + 1, input + start, len + 1);
	value[len + 1] = quote;
	value[len + 2] = '\0';
	return (value);
}

t_token	*create_quoted_token(char *value, size_t start, size_t end, char quote)
{
	t_token	*token;
	char	*clean_value;

	clean_value = remove_quotes(value);
	if (!clean_value)
		return (NULL);
	token = gc_alloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = clean_value;
	token->type = TOKEN_WORD;
	token->can_expand = (quote == DOUBLE_QUOTES);
	token->start_index = start;
	token->end_index = end;
	token->from_expansion = 0;
	token->is_heredoc_delim = 0;
	return (token);
}
