/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/05/09 15:49:42 by ahlahfid         ###   ########.fr       */
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
	size_t	argc;
	char	**argv;
	t_list	*tmp;
	size_t	i;

	argc = ft_lstsize(argv_list);
	argv = gc_malloc(&gc, sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	tmp = argv_list;
	i = 0;
	while (i < argc)
	{
		argv[i] = ft_strdup(tmp->content);
		if (!argv[i])
		{
			while (i > 0)
				free(argv[--i]);
			free(argv);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
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
	return -1; // error
}

