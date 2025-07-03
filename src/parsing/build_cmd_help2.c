/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_help2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/07/03 15:47:41 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"

int	handle_redirection_token(t_cmd *cmd, int *redir_i, t_list **tokens)
{
	t_token	*redir;

	redir = (*tokens)->content;
	if (!(*tokens)->next
		|| ((t_token *)(*tokens)->next->content)->type != TOKEN_WORD)
	{
		print_parse_error(ERR_NEAR_NEWLINE, NULL);
		return (1);
	}
	add_redirection(&cmd->redirs[(*redir_i)++], redir,
		(*tokens)->next->content);
	(*tokens) = (*tokens)->next;
	return (0);
}

void	handle_word_token(t_cmd *cmd, t_token *tok, int *arg_i)
{
	char	**split_args;
	int		i;

	if (tok->from_expansion && !tok->quoted_2)
	{
		printf("Expanding: %s\n", tok->value);
		split_args = gc_split(tok->value);
		if (split_args)
		{
			i = 0;
			while (split_args[i])
			{
				if (ft_strlen(split_args[i]) > 0)
					cmd->argv[(*arg_i)++] = split_args[i];
				i++;
			}
		}
	}
	else
		cmd->argv[(*arg_i)++] = remove_quotes(tok->value, NULL);
}

int	handle_pipe_token(t_list **tokens, t_cmd *cmd)
{
	if ((*tokens)->next
		&& ((t_token *)(*tokens)->next->content)->type == TOKEN_PIPE)
	{
		print_parse_error(ERR_UNEXPECTED_TOKEN, "||");
		return (1);
	}
	if (!(*tokens)->next)
	{
		print_parse_error(ERR_NEAR_NEWLINE, NULL);
		return (1);
	}
	cmd->is_pipe = 1;
	(*tokens) = (*tokens)->next;
	return (0);
}

int	parse_cmd_tokens(t_cmd *cmd, t_list **tokens, int *arg_i, int *redir_i)
{
	t_token	*tok;

	while (*tokens)
	{
		tok = (*tokens)->content;
		if (tok->type == TOKEN_PIPE)
		{
			if (handle_pipe_token(tokens, cmd))
				return (1);
			break ;
		}
		else if (tok->type == TOKEN_WORD)
			handle_word_token(cmd, tok, arg_i);
		else if (tok->type >= TOKEN_REDIR_IN && tok->type <= TOKEN_HEREDOC)
		{
			if (handle_redirection_token(cmd, redir_i, tokens))
				return (1);
		}
		(*tokens) = (*tokens)->next;
	}
	return (0);
}

int	check_pipe_start(t_list *tokens)
{
	if (tokens && ((t_token *)tokens->content)->type == TOKEN_PIPE)
	{
		print_parse_error(ERR_UNEXPECTED_TOKEN, "|");
		return (1);
	}
	return (0);
}
