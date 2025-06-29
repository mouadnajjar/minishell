/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_help3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/28 18:12:21 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/executor.h"

int	is_pipe_token(t_list *tokens)
{
	t_token	*tok;

	tok = tokens->content;
	return (tok->type == TOKEN_PIPE);
}

int	is_word_token(t_list *tokens)
{
	t_token	*tok;

	tok = tokens->content;
	return (tok->type == TOKEN_WORD);
}

int	count_token_args(t_token *tok)
{
	char	**split_args;
	int		count;
	int		i;

	count = 0;
	if (tok->from_expansion)
	{
		split_args = gc_split(tok->value);
		if (split_args)
		{
			i = 0;
			while (split_args[i])
			{
				if (ft_strlen(split_args[i]) > 0)
					count++;
				i++;
			}
		}
	}
	else
	{
		count++;
	}
	return (count);
}

int	count_args(t_list *tokens)
{
	int		count;
	t_token	*tok;

	count = 0;
	while (tokens)
	{
		if (is_pipe_token(tokens))
			break ;
		if (is_word_token(tokens))
		{
			tok = tokens->content;
			count += count_token_args(tok);
		}
		tokens = tokens->next;
	}
	return (count);
}
