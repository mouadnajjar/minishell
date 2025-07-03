/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/07/03 15:48:04 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

int	add_redirection(t_redirect *redir, t_token *redir_op, t_token *target)
{
	redir->ambiguous_redirect = target->ambiguous_redirect;
	redir->ambg_name = target->ambg_name;
	redir->type = get_redir_type(redir_op->type);
	if (redir_op->type == TOKEN_HEREDOC && target->is_heredoc_delim)
	{
		redir->quoted = is_quoted(target->value);
		redir->target = remove_quotes(target->value, NULL);
		redir->heredoc_fd = -1;
	}
	else
	{
		redir->target = remove_quotes(target->value, NULL);
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
	i = 0;
	if (!s)
		return (0);
	while (i < len - 1)
	{
		if (s[i] == SINGLE_QUOTES || s[i] == DOUBLE_QUOTES)
			return (1);
		i++;
	}
	return (0);
}

int	is_quoted_origin(const char *s)
{
	int	len;
	int	i;

	len = ft_strlen(s);
	i = 0;
	if (!s)
		return (0);
	while (i < len)
	{
		if (s[i] == '\'' || s[i] == '"')
			return (1);
		i++;
	}
	return (0);
}
