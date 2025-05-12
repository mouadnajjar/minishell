/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/05/12 13:21:26 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

t_token	*handle_quoted_token(const char *input, size_t *i)
{
	t_token_type	type;
	size_t			start;
	char			quote;

	quote = input[*i]; // ' or "
	if (quote == '\'')
		type = TOKEN_QUOTE_SINGLE;
	else
		type = TOKEN_QUOTE_DOUBLE;
	start = *i + 1;
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (!input[*i]) // Unclosed quote
		return (NULL);
	return (create_token(type, input + start, *i - start));
}

t_token	*create_token(t_token_type type, const char *value, size_t len)
{
	t_token	*token;

	if (!value) // Validate input
		return (NULL);
	token = gc_malloc(&gc, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = gc_malloc(&gc, len + 1);
	// Allocate space for null terminator
	if (!token->value)
		return (NULL);
	ft_strlcpy(token->value, value, len + 1); // Ensure null termination
	token->next = NULL;
	return (token);
}
t_token	*handle_special_token(const char *input, size_t *i)
{
	if (input[*i] == '|')
	{
		(*i)++;
		return (create_token(TOKEN_PIPE, "|", 1));
	}
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		*i += 2;
		return (create_token(TOKEN_HEREDOC, "<<", 2));
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		*i += 2;
		return (create_token(TOKEN_APPEND, ">>", 2));
	}
	else if (input[*i] == '<')
	{
		(*i)++;
		return (create_token(TOKEN_REDIR_IN, "<", 1));
	}
	else if (input[*i] == '>')
	{
		(*i)++;
		return (create_token(TOKEN_REDIR_OUT, ">", 1));
	}
	return (NULL);
}

t_token	*handle_word_token(const char *input, size_t *i)
{
	size_t	start;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !ft_strchr("|<>", input[*i]))
		(*i)++;
	return (create_token(TOKEN_WORD, input + start, *i - start));
}

t_token	*lexer(const char *input)
{
	t_token	*head;
	t_token	*current;
	size_t	i;
	t_token	*token;

	head = NULL;
	current = NULL;
	i = 0;
	while (input[i])
	{
		i = skip_whitespace(input, i);
		if (!input[i])
			break ;
		token = NULL;
		if (input[i] == '\'' || input[i] == '"')
			token = handle_quoted_token(input, &i);
		else if (ft_strchr("|<>", input[i]))
			token = handle_special_token(input, &i);
		else
			token = handle_word_token(input, &i);
		if (!token)
			return (NULL);
		if (!head)
			head = token;
		else
			current->next = token;
		current = token;
		if (input[i]) // Move past closing quote if present
			i++;
	}
	return (head);
}
