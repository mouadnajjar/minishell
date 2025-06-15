/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/15 15:09:07 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

void	print_parse_error(t_parse_error code,char *str)
{

	if (code == ERR_UNCLOSED_QUOTE)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
		ft_putchar_fd(str[0], 2);
		ft_putstr_fd("'\n", 2);
		g_shell.last_exit_status = 2;
	}
	else if (code == ERR_HEREDOC_DELIM)
	{
		ft_putstr_fd("minishell: warning: heredoc delimited by end-of-file (wanted `",2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("')\n", 2);
		g_shell.last_exit_status = 0;
	}
	else if (code == ERR_UNEXPECTED_TOKEN)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("'\n", 2);
		g_shell.last_exit_status = 2;
	}
	else if (code == ERR_NEAR_NEWLINE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		g_shell.last_exit_status = 2;
	}
	else if (code == ERR_EMPTY_COMMAND)
	{
		ft_putstr_fd("minishell: syntax error: empty command\n", 2);
		g_shell.last_exit_status = 2;
	}
}
int is_invalid_redir(const char *s)
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
