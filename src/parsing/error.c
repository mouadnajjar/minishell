/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/29 11:14:51 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

void	unclosed_quote(char *str)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(str[0], 2);
	ft_putstr_fd("'\n", 2);
	g_shell.last_exit_status = 2;
}

void	print_parse_error(t_parse_error code, char *str)
{
	if (code == ERR_UNCLOSED_QUOTE)
		unclosed_quote(str);
	else if (code == ERR_HEREDOC_DELIM)
		heredoc_delim(str);
	else if (code == ERR_UNEXPECTED_TOKEN)
		unexpected_token(str);
	else if (code == ERR_NEAR_NEWLINE)
		near_newline();
	else if (code == ERR_EMPTY_COMMAND)
		empty_command();
	else if (code == ERR_MAX_HEREDOCS_EXCEEDED)
		max_heredocs_exceeded();
}

int	is_invalid_redir(const char *s)
{
	if (!s)
		return (0);
	if (ft_strncmp(s, ">", 2) == 0 || ft_strncmp(s, ">>", 3) == 0
		|| ft_strncmp(s, "<", 2) == 0 || ft_strncmp(s, "<<", 3) == 0)
		return (1);
	if (ft_strnstr(s, "<>", ft_strlen(s)) || ft_strnstr(s, "><", ft_strlen(s)))
		return (1);
	return (0);
}

int	is_valid_redirection(const char *s)
{
	return (ft_strncmp(s, "<", 2) == 0 || ft_strncmp(s, "<<", 3) == 0
		|| ft_strncmp(s, ">", 2) == 0 || ft_strncmp(s, ">>", 3) == 0
		|| ft_strncmp(s, "|", 2) == 0);
}
