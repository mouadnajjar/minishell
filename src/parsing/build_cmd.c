/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/28 16:27:19 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

t_cmd	*init_cmd_struct(t_list **tokens)
{
	t_cmd	*cmd;
	int		argc;

	cmd = gc_alloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->is_pipe = 0;
	cmd->next = NULL;
	argc = count_args(*tokens);
	cmd->argv = gc_alloc(sizeof(char *) * (argc + 1));
	cmd->redir_count = count_redirections(*tokens);
	cmd->redirs = gc_alloc(sizeof(t_redirect) * (cmd->redir_count + 1));
	return (cmd);
}

t_cmd	*build_single_cmd(t_list **tokens)
{
	t_cmd	*cmd;
	int		arg_i;
	int		redir_i;
	int		argc;

	if (check_pipe_start(*tokens))
		return (NULL);
	cmd = init_cmd_struct(tokens);
	if (!cmd)
		return (NULL);
	arg_i = 0;
	redir_i = 0;
	if (parse_cmd_tokens(cmd, tokens, &arg_i, &redir_i))
		return (NULL);
	argc = count_args(*tokens);
	if (arg_i <= argc && cmd->argv)
		cmd->argv[arg_i] = NULL;
	if (redir_i <= cmd->redir_count && cmd->redirs)
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
