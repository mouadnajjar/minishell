/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/29 11:20:18 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

void	heredoc_delim(char *str)
{
	char	*tmp;

	tmp = "minishell: warning: heredoc delimited by end-of-file (wanted `";
	ft_putstr_fd(tmp, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("')\n", 2);
	g_shell.last_exit_status = 0;
}

void	unexpected_token(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	g_shell.last_exit_status = 2;
}

void	near_newline(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
		2);
	g_shell.last_exit_status = 2;
}

void	empty_command(void)
{
	ft_putstr_fd("minishell: syntax error: empty command\n", 2);
	g_shell.last_exit_status = 2;
}

void	max_heredocs_exceeded(void)
{
	ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
	g_shell.last_exit_status = 2;
	gc_free_all();
	exit(2);
}
