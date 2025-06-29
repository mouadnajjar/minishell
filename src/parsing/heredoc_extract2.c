/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_extract2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/27 19:07:09 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"

t_token	*create_quoted_token_heredoc(char *value, size_t start, size_t end,
		char quote)
{
	t_token	*token;
	char	*clean_value;

	clean_value = value;
	token = gc_alloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = clean_value;
	token->type = TOKEN_WORD;
	token->can_expand = (quote == DOUBLE_QUOTES);
	token->start_index = start;
	token->end_index = end;
	return (token);
}

char	*alloc_quoted_value_heredoc(const char *input, size_t start, size_t len)
{
	char	*value;

	value = gc_alloc(len + 1);
	if (!value)
		return (NULL);
	ft_strlcpy(value, input + start, len + 1);
	return (value);
}
