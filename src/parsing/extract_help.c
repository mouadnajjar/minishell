/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/17 11:38:03 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

t_token_type	get_operator_type(const char *op)
{
	if (ft_strncmp(op, "|", 2) == 0)
		return (TOKEN_PIPE);
	if (ft_strncmp(op, "<", 2) == 0)
		return (TOKEN_REDIR_IN);
	if (ft_strncmp(op, ">", 2) == 0)
		return (TOKEN_REDIR_OUT);
	if (ft_strncmp(op, ">>", 3) == 0)
		return (TOKEN_REDIR_APPEND);
	if (ft_strncmp(op, "<<", 3) == 0)
		return (TOKEN_HEREDOC);
	return (TOKEN_INVALID);
}

char	*get_operator(const char *input, size_t *i)
{
	size_t	start;
	int		len;
	char	c;

	len = 0;
	start = *i;
	if (input[*i] != '<' && input[*i] != '>' && input[*i] != '|')
		return (NULL);
	c = input[*i];
	while (input[*i] == c && len < 2)
	{
		len++;
		(*i)++;
	}
	return (gc_substr(input, start, *i - start));
}

int	is_word_end(char c)
{
	return (c == '\0' || ft_isspace(c) || c == '|' || c == '<' || c == '>'
		|| c == '\'' || c == '"');
}
