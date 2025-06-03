/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/03 21:32:05 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

t_token	*handle_quoted_token(const char *input, size_t *i)
{
	t_token_type	type;
	size_t			start;
	char			quote;
	t_token			*token;

	quote = input[*i];
	if (quote == '\'')
		type = TOKEN_QUOTE_SINGLE;
	else if (quote == '"')
		type = TOKEN_QUOTE_DOUBLE;
	else
		return (NULL);
	start = *i + 1;
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (!input[*i]) // Unclosed quote
	{
		ft_putstr_fd("minishell: unclosed quote\n", 2);
		return (NULL);
	}
	token = create_token(type, input + start, *i - start);
	(*i)++; // Move past closing quote
	return (token);
}

t_token	*create_token(t_token_type type, const char *value, size_t len)
{
	t_token	*token;

	if (!value)
		return (NULL);
	token = gc_malloc(&gc, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = gc_malloc(&gc, len + 1);
	if (!token->value)
		return (NULL);
	ft_strlcpy(token->value, value, len + 1);
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
	while (input[*i] && !ft_isspace(input[*i]) && !ft_strchr("|<>", input[*i])
		&& input[*i] != '\'' && input[*i] != '"')
		(*i)++;
	return (create_token(TOKEN_WORD, input + start, *i - start));
}
static char	*handle_quoted_segment(const char *input, size_t *i,
	t_token_type *type)
{
	char	quote;
	size_t	start;
	size_t	len;
	char	*segment;

	quote = input[(*i)++];
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (!input[*i])  // Unclosed quote
	{
		ft_putstr_fd("minishell: unclosed quote\n", 2);
		return (NULL);
	}
	len = *i - start;
	segment = ft_substr(input, start, len);  // Will return "" if empty
	if (!segment)
		return (NULL);
	(*i)++;  // Skip closing quote
	if (quote == '\'')
	{
		if (*type != TOKEN_QUOTE_DOUBLE)
			*type = TOKEN_QUOTE_SINGLE;
	}
	else if (quote == '\"')
		*type = TOKEN_QUOTE_DOUBLE;
	return (segment);  // Even "" is valid
}


static char	*handle_unquoted_segment(const char *input, size_t *i)
{
	size_t	start;
	size_t	len;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !ft_strchr("|<>", input[*i])
		&& input[*i] != '\'' && input[*i] != '"')
		(*i)++;
	len = *i - start;
	return (ft_substr(input, start, len));
}
t_token *extract_word(const char *input, size_t *i)
{
	t_token_type type = TOKEN_WORD;
	char *value = ft_strdup("");
	if (!value)
		return NULL;

	int can_expand = 0;

	while (input[*i] && !ft_isspace(input[*i]) && !ft_strchr("|<>", input[*i]))
	{
		char *segment = NULL;
		t_token_type segment_type = TOKEN_WORD;

		if (input[*i] == '\'' || input[*i] == '"')
		{
			segment = handle_quoted_segment(input, i, &segment_type);
			if (segment_type != TOKEN_QUOTE_SINGLE)
				can_expand = 1;
		}
		else
		{
			segment = handle_unquoted_segment(input, i);
			can_expand = 1;
		}

		if (!segment)
		{
			ft_putstr_fd("minishell: tokenization error (segment)\n", 2);
			free(value);
			return NULL;
		}

		char *tmp = ft_strjoin(value, segment);
		free(value);
		free(segment);
		if (!tmp)
			return NULL;
		value = tmp;

		// 🔥 Key logic: stop here and return token to split at quote boundary
		if ((segment_type == TOKEN_QUOTE_SINGLE || segment_type == TOKEN_QUOTE_DOUBLE) &&
			input[*i] && !ft_isspace(input[*i]) && !ft_strchr("|<>", input[*i]) &&
			input[*i] != '\'' && input[*i] != '"')
		{
			break;
		}
	}

	t_token *token = create_token(type, value, ft_strlen(value));
	if (!token)
	{
		free(value);
		return NULL;
	}
	token->can_expand = can_expand;
	token->merge_next = (input[*i] && !ft_isspace(input[*i]) && !ft_strchr("|<>", input[*i])) ? 1 : 0;

	return token;
}


t_token	*lexer(const char *input)
{
	t_token	*head = NULL;
	t_token	*current = NULL;
	t_token	*token;
	size_t	i;

	i = 0;
	while (input[i])
	{
		i = skip_whitespace(input, i);
		if (!input[i])
			break ;
		if (ft_strchr("|<>", input[i]))
			token = handle_special_token(input, &i);
		else
			token = extract_word(input, &i);
		if (!token)
		{
			ft_putstr_fd("minishell: tokenization failed\n", 2);
			// 🚨 Removed gc_free_all here
			// Let main.c handle cleanup
			return (NULL);
		}
		if (!head)
			head = token;
		else
			current->next = token;
		current = token;
	}
	return (head);
}

