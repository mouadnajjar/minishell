/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/05/25 13:26:52 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = gc_malloc(&gc, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirs = NULL;
	cmd->is_pipe = 0;
	cmd->next = NULL;
	return (cmd);
}
char	**list_to_argv(t_list *argv_list)
{
    size_t	argc = 0;
    t_list	*tmp = argv_list;

    // Count non-empty arguments
    while (tmp)
    {
        char *s = (char *)tmp->content;
        if (s && s[0] != '\0')
            argc++;
        tmp = tmp->next;
    }
    char **argv = gc_malloc(&gc, sizeof(char *) * (argc + 1));
    if (!argv)
        return (NULL);
    tmp = argv_list;
    size_t i = 0;
    while (tmp)
    {
        char *s = (char *)tmp->content;
        if (s && s[0] != '\0')
            argv[i++] = s;
        tmp = tmp->next;
    }
    argv[i] = NULL;
    ft_lstclear(&argv_list, NULL);
    return (argv);
}

t_redirect	*list_to_redirs(t_list *redir_list)
{
	size_t		redirc;
	t_redirect	*redirs;
	t_list		*tmp;
	size_t		i;

	redirc = ft_lstsize(redir_list);
	redirs = gc_malloc(&gc, sizeof(t_redirect) * (redirc + 1));
	if (!redirs)
		return (NULL);
	tmp = redir_list;
	i = 0;
	while (i < redirc)
	{
		redirs[i] = *(t_redirect *)tmp->content;
		redirs[i].target = ft_strdup(redirs[i].target);
		if (!redirs[i].target)
		{
			while (i > 0)
				free(redirs[--i].target);
			free(redirs);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	redirs[i].target = NULL;
	ft_lstclear(&redir_list, NULL);
	return (redirs);
}
t_redir_type get_redir_type(t_token_type token_type)
{
	if (token_type == TOKEN_REDIR_IN)
		return IN;
	if (token_type == TOKEN_REDIR_OUT)
		return OUT;
	if (token_type == TOKEN_APPEND)
		return APPEND;
	if (token_type == TOKEN_HEREDOC)
		return HEREDOC;
	return -1;
}

int redirection_token(t_token **current, t_list **redir_list)
{
    t_redirect *redir;
    t_list *node;

    // Validate current token and next token
    if (!*current || !(*current)->next || (*current)->next->type != TOKEN_WORD)
        return (-1);

    redir = gc_malloc(&gc, sizeof(t_redirect));
    if (!redir)
        return (-1);

    redir->target = (*current)->next->value; // Save filename
    redir->type = get_redir_type((*current)->type);

    node = gc_malloc(&gc, sizeof(t_list));
    if (!node)
        return (-1);

    node->content = redir;
    node->next = NULL;
    ft_lstadd_back(redir_list, node);

    *current = (*current)->next->next;  // Skip both the redirection token and filename
    return (0);
}


