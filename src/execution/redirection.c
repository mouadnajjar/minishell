/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:50:03 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/15 16:06:13 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"

void	handle_input_redir(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		g_shell.last_exit_status = 1;
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	handle_output_redir(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(file);
		g_shell.last_exit_status = 1;
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_append_redir(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(file);
		g_shell.last_exit_status = 1;
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

int	apply_redirections(t_redirect *redirs)
{
	int	i;

	i = 0;
	while (redirs && redirs[i].target)
	{
		if (redirs[i].type == IN)
			handle_input_redir(redirs[i].target);
		else if (redirs[i].type == OUT || redirs[i].type == TRUNCATE)
			handle_output_redir(redirs[i].target);
		else if (redirs[i].type == APPEND)
			handle_append_redir(redirs[i].target);
		else if (redirs[i].type == HEREDOC && redirs[i].heredoc_fd != -1)
		{
			if (dup2(redirs[i].heredoc_fd, STDIN_FILENO) == -1)
			{
				ft_putendl_fd("dup2", 2);
				return (1);
			}
			close(redirs[i].heredoc_fd);
		}
		if (g_shell.last_exit_status == 1)
			return (1);
		i++;
	}
	return (0);
}
