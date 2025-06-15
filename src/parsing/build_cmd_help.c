/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/14 20:29:05 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

int	count_args(t_list *tokens)
{
	int		count;
	t_token	*tok;

	count = 0;
	while (tokens)
	{
		tok = tokens->content;
		if (tok->type == TOKEN_PIPE)
			break ;
		if (tok->type == TOKEN_WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

int	add_redirection(t_redirect *redir, t_token *redir_op, t_token *target)
{
	redir->type = get_redir_type(redir_op->type);
	if (redir_op->type == TOKEN_HEREDOC && target->is_heredoc_delim)
	{
		redir->quoted = is_quoted(target->value);
		if (redir->quoted)
			redir->target = remove_quotes(target->value);
		else
			redir->target = remove_quotes(target->value);
		redir->heredoc_fd = -1;
	}
	else
	{
		redir->target = remove_quotes(target->value);
		redir->quoted = 0;
		redir->heredoc_fd = -1;
	}
	return (0);
}

t_redir_type	get_redir_type(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (IN);
	if (type == TOKEN_REDIR_OUT)
		return (OUT);
	if (type == TOKEN_REDIR_APPEND)
		return (APPEND);
	if (type == TOKEN_HEREDOC)
		return (HEREDOC);
	return (-1);
}

int	count_redirections(t_list *tokens)
{
	int		count;
	t_token	*tok;

	count = 0;
	while (tokens)
	{
		tok = tokens->content;
		if (tok->type >= TOKEN_REDIR_IN && tok->type <= TOKEN_HEREDOC)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

int	is_quoted(const char *s)
{
	int	len;
	int	i;

	len = ft_strlen(s);
	i = 1;
	if (!s || len < 2)
		return (0);
	while (i < len - 1)
	{
		if ((s[i] == '\'' && s[len - 1] == '\'') || (s[i] == '"' && s[len
					- 1] == '"'))
			return (1);
		i++;
	}
	return (0);
}
