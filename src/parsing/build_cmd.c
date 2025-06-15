/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/14 20:29:11 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

t_cmd	*init_cmd_struct(t_list **tokens)
{
	t_cmd	*cmd;
	int		argc;

	cmd = gc_alloc(sizeof(t_cmd), &gc);
	if (!cmd)
		return (NULL);
	cmd->is_pipe = 0;
	cmd->next = NULL;
	argc = count_args(*tokens);
	cmd->argv = gc_alloc(sizeof(char *) * (argc + 1), &gc);
	cmd->redir_count = count_redirections(*tokens);
	cmd->redirs = gc_alloc(sizeof(t_redirect) * (cmd->redir_count + 1), &gc);
	return (cmd);
}

t_cmd	*build_single_cmd(t_list **tokens)
{
	t_cmd	*cmd;
	int		arg_i;
	int		redir_i;

	if (check_pipe_start(*tokens))
		return (NULL);
	cmd = init_cmd_struct(tokens);
	if (!cmd)
		return (NULL);
	arg_i = 0;
	redir_i = 0;
	if (parse_cmd_tokens(cmd, tokens, &arg_i, &redir_i))
		return (NULL);
	cmd->argv[arg_i] = NULL;
	cmd->redirs[redir_i].target = NULL;
	return (cmd);
}

t_cmd	*build_commands(t_list *tokens)
{
	t_cmd	*head;
	t_cmd	*last;
	t_cmd	*cmd;

	head = NULL;
	last = NULL;
	while (tokens)
	{
		cmd = build_single_cmd(&tokens);
		if (!cmd)
			return (NULL);
		if (!head)
			head = cmd;
		else
			last->next = cmd;
		last = cmd;
	}
	return (head);
}

// build_commands.c
// t_cmd	*build_single_cmd(t_list **tokens)
// {
// 	t_cmd *cmd = gc_alloc(sizeof(t_cmd), &gc);
// 	if (!cmd)
// 		return (NULL);

// 	cmd->is_pipe = 0;
// 	cmd->next = NULL;

// 	int argc = count_args(*tokens);
// 	cmd->argv = gc_alloc(sizeof(char *) * (argc + 1), &gc);
// 	if (!cmd->argv)
// 		return (NULL);

// 	// ✅ Count redirections and allocate array (+1 for NULL sentinel)
// 	cmd->redir_count = count_redirections(*tokens);
// 	cmd->redirs = gc_alloc(sizeof(t_redirect) * (cmd->redir_count + 1), &gc);

// 	int i = 0;
// 	int redir_i = 0;

// 	if (*tokens && ((t_token *)(*tokens)->content)->type == TOKEN_PIPE)
// 	{
// 		print_parse_error(ERR_UNEXPECTED_TOKEN, "|");
// 		return (NULL);
// 	}

// 	while (*tokens)
// 	{
// 		t_token *tok = (*tokens)->content;

// 		if (tok->type == TOKEN_PIPE)
// 		{
// 			if ((*tokens)->next
//				&& ((t_token *)(*tokens)->next->content)->type == TOKEN_PIPE)
// 			{
// 				print_parse_error(ERR_UNEXPECTED_TOKEN, "||");
// 				return (NULL);
// 			}
// 			if (!(*tokens)->next)
// 			{
// 				print_parse_error(ERR_NEAR_NEWLINE, NULL);
// 				return (NULL);
// 			}
// 			cmd->is_pipe = 1;
// 			(*tokens) = (*tokens)->next;
// 			break ;
// 		}
// 		else if (tok->type == TOKEN_WORD)
// 		{
// 			cmd->argv[i++] = remove_quotes(tok->value);
// 		}
// 		else if (tok->type >= TOKEN_REDIR_IN && tok->type <= TOKEN_HEREDOC)
// 		{
// 			if (!(*tokens)->next
//				|| ((t_token *)(*tokens)->next->content)->type != TOKEN_WORD)
// 			{
// 				print_parse_error(ERR_NEAR_NEWLINE, NULL);
// 				return (NULL);
// 			}
// 			add_redirection(&cmd->redirs[redir_i++], tok,
//				(*tokens)->next->content);
// 			(*tokens) = (*tokens)->next;
// 		}
// 		(*tokens) = (*tokens)->next;
// 	}
// 	// ✅ Terminate argv and redir array
// 	cmd->argv[i] = NULL;
// 	cmd->redirs[redir_i].target = NULL;

// 	return (cmd);
// }
