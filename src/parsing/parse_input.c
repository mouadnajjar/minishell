/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/05/12 15:13:16 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

int	word_token(t_token *current, t_list **argv_list)
{
	t_list	*node;

	node = gc_malloc(&gc, sizeof(t_list));
	if (!node)
		return (-1);
	node->content = current->value;
	node->next = NULL;
	ft_lstadd_back(argv_list, node);
	return (0);
}

int	redirection_token(t_token **current, t_list **redir_list)
{
	t_redirect	*redir;
	t_list		*node;

	redir = gc_malloc(&gc, sizeof(t_redirect));
	if (!redir || !(*current)->next || (*current)->next->type != TOKEN_WORD)
		return (-1);
	redir->target = (*current)->next->value;
	redir->type = get_redir_type((*current)->type);
	node = gc_malloc(&gc, sizeof(t_list));
	if (!node)
		return (-1);
	node->content = redir;
	node->next = NULL;
	ft_lstadd_back(redir_list, node);
	*current = (*current)->next;
	return (0);
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
		if (!tmp)
			return (-1);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = *current_cmd;
	}
	*current_cmd = NULL;
	*argv_list = NULL;
	*redir_list = NULL;
	return (0);
}
t_cmd	*parser(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current_cmd;
	t_token	*current;
	t_list	*argv_list;
	t_list	*redir_list;

	head = NULL;
	current_cmd = NULL;
	current = tokens;
	argv_list = NULL;
	redir_list = NULL;
	while (current)
	{
		if (!current_cmd)
		{
			current_cmd = init_cmd();
			if (!current_cmd)
				return (NULL);
		}
		if (current->type == TOKEN_WORD || current->type == TOKEN_QUOTE_SINGLE || current->type == TOKEN_QUOTE_DOUBLE)
        {
            if (word_token(current, &argv_list) < 0)
                return (NULL);
		}
		else if (current->type == TOKEN_REDIR_OUT
			|| current->type == TOKEN_REDIR_IN || current->type == TOKEN_APPEND
			|| current->type == TOKEN_HEREDOC)
		{
			if (redirection_token(&current, &redir_list) < 0)
				return (NULL);
		}
		else if (current->type == TOKEN_PIPE)
		{
			current_cmd->is_pipe = 1; // Set pipe flag before finalizing
			if (finalize_cmd(&current_cmd, &argv_list, &redir_list, &head) < 0)
				return (NULL);
			current_cmd = init_cmd(); // Reinitialize for next command
			if (!current_cmd)
				return (NULL);
		}
		current = current->next;
	}
	if (current_cmd)
	{
		if (finalize_cmd(&current_cmd, &argv_list, &redir_list, &head) < 0)
			return (NULL);
	}
	return (head);
}

t_cmd *parse_input(const char *input)
{
    t_token *tokens;
    t_cmd *cmd;
    t_token *tmp;

    tokens = lexer(input);
    cmd = NULL;
    if (!tokens)
    {
        ft_putstr_fd("minishell: unclosed quote\n", 2);
        return (NULL);
    }
    tmp = tokens;
    while (tmp)
    {
        printf("Token: %s (type: %d)\n", tmp->value, tmp->type);
        tmp = tmp->next;
    }
    cmd = parser(tokens);
    return (cmd);
}
