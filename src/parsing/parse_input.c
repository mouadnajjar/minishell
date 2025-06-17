/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/16 20:00:59 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

t_cmd	*parse_input(char *input)
{
	t_list	*tokens;
	t_cmd	*cmds;

	tokens = split_input(input);
	if (!tokens)
		return (NULL);
	expand_tokens(tokens);
	merge_adjacent_words(&tokens, input);
	cmds = build_commands(tokens);
	process_heredocs(cmds);
	return (cmds);
}
