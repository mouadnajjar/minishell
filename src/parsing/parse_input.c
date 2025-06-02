/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/02 15:23:05 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "minishell.h"
#include <stdio.h>

int	word_token(t_token *current, t_list **argv_list, t_token **out_next)
{
	t_list	*node;
	char	*value;
	t_token	*next;
	char	*temp;

	// Start with current token value
	value = ft_strdup(current->value);
	if (!value)
		return (-1);
	// Merge adjacent quoted tokens
	next = current->next;
	while (next && (next->type == TOKEN_QUOTE_SINGLE
			|| next->type == TOKEN_QUOTE_DOUBLE))
	{
		temp = ft_strjoin(value, next->value);
		free(value);
		if (!temp)
			return (-1);
		value = temp;
		next = next->next;
	}
	node = ft_lstnew(value);
	if (!node)
		return (free(value), -1);
	ft_lstadd_back(argv_list, node);
	*out_next = next;
	return (0);
}

const char	*redir_type_to_str(t_redir_type type)
{
	if (type == IN)
		return ("IN");
	if (type == OUT)
		return ("OUT");
	if (type == APPEND)
		return ("APPEND");
	if (type == HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

int	finalize_cmd(t_cmd **current_cmd, t_list **argv_list, t_list **redir_list,
		t_cmd **head)
{
	t_cmd	*tmp;

	if (!*argv_list && !*redir_list)
		return (-1);
	(*current_cmd)->argv = list_to_argv(*argv_list);
	if (*argv_list && !(*current_cmd)->argv)
		return (-1);
	(*current_cmd)->redirs = list_to_redirs(*redir_list);
	if (*redir_list && !(*current_cmd)->redirs)
		return (-1);
	if (!*head)
		*head = *current_cmd;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = *current_cmd;
	}
	*current_cmd = NULL;
	*argv_list = NULL;
	*redir_list = NULL;
	return (0);
}

static char	*expand_argument(t_token *token)
{
	char	*expanded;

	if (!token || !token->value)
		return (NULL);
	if (token->type == TOKEN_QUOTE_SINGLE)
		return (ft_strdup(token->value));
	expanded = expand_variables(token->value);
	if (expanded)
		return (expanded);
	return (ft_strdup(token->value));
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*head = NULL;
	t_cmd	*current_cmd = NULL;
	t_token	*current = tokens;
	t_list	*argv_list = NULL;
	t_list	*redir_list = NULL;
	t_list	*node;

	while (current)
	{
		if (!current_cmd)
		{
			current_cmd = init_cmd();
			if (!current_cmd)
			{
				gc_free_all(&gc); // Free all tracked allocations
				return (NULL);
			}
		}

		if (current->type == TOKEN_WORD || current->type == TOKEN_QUOTE_SINGLE
			|| current->type == TOKEN_QUOTE_DOUBLE)
		{
			node = ft_lstnew(expand_argument(current));
			if (!node)
			{
				gc_free_all(&gc); // Free all tracked allocations
				return (NULL);
			}
			ft_lstadd_back(&argv_list, node);
		}
		else if (current->type == TOKEN_REDIR_OUT
			|| current->type == TOKEN_REDIR_IN || current->type == TOKEN_APPEND
			|| current->type == TOKEN_HEREDOC)
		{
			if (redirection_token(&current, &redir_list) < 0)
			{
				gc_free_all(&gc); // Free all tracked allocations
				return (NULL);
			}
			continue;
		}
		else if (current->type == TOKEN_PIPE)
		{
			current_cmd->is_pipe = 1;
			if (finalize_cmd(&current_cmd, &argv_list, &redir_list, &head) < 0)
			{
				gc_free_all(&gc); // Free all tracked allocations
				return (NULL);
			}
			current_cmd = init_cmd();
			if (!current_cmd)
			{
				gc_free_all(&gc); // Free all tracked allocations
				return (NULL);
			}
		}

		current = current->next;
	}

	if (current_cmd)
	{
		if (finalize_cmd(&current_cmd, &argv_list, &redir_list, &head) < 0)
		{
			gc_free_all(&gc); // Free all tracked allocations
			return (NULL);
		}
	}

	return (head);
}

t_cmd	*parse_input(const char *input)
{
	t_token	*tokens;
	t_cmd	*cmd;
	t_token	*tmp;
	int		i;
	t_cmd	*current;
	int		cmd_index;

	tokens = lexer(input);
	if (!tokens)
	{
		ft_putstr_fd("minishell: void token\n", 2);
		return (NULL);  // 🚨 No cleanup here, let main.c handle it
	}

	// Debug: print tokens
	printf("=== Tokens ===\n");
	tmp = tokens;
	while (tmp)
	{
		printf("Token: %s (type: %d)\n", tmp->value, tmp->type);
		tmp = tmp->next;
	}
	printf("=== End of Tokens ===\n");

	cmd = parser(tokens);
	if (!cmd)
	{
		ft_putstr_fd("minishell: parsing failed\n", 2);
		// 🚨 No cleanup here, main.c will handle gc_free_all and readline input
		return (NULL);
	}

	// Debug: print parsed commands
	printf("=== Parsed Commands ===\n");
	current = cmd;
	cmd_index = 0;
	while (current)
	{
		printf("Command %d:\n", cmd_index);
		printf("  argv:\n");
		if (current->argv)
		{
			for (i = 0; current->argv[i]; i++)
				printf("    arg[%d] = %s\n", i, current->argv[i]);
		}
		else
			printf("    (no arguments)\n");

		printf("  redirs:\n");
		if (current->redirs)
		{
			for (i = 0; current->redirs[i].target; i++)
				printf("    redir[%d] = %s (type: %s)\n", i,
					current->redirs[i].target,
					redir_type_to_str(current->redirs[i].type));
		}
		else
			printf("    (no redirections)\n");

		printf("  is_pipe: %d\n", current->is_pipe);
		printf("  next: %s\n", current->next ? "present" : "none");
		current = current->next;
		cmd_index++;
	}
	printf("=== End of Parsed Commands ===\n");
	printf("============================================\n");

	return (cmd);
}
