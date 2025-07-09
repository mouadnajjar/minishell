/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:50:03 by monajjar          #+#    #+#             */
/*   Updated: 2025/07/05 12:53:35 by monajjar         ###   ########.fr       */
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

int	check_ambiguous(t_redirect *redirs)
{
	if (redirs->ambiguous_redirect == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("$", 2);
		ft_putstr_fd(redirs->ambg_name, 2);
		ft_putendl_fd(": ambiguous redirect", 2);
		redirs->ambg_name = NULL;
		redirs->ambiguous_redirect = 0;
		return (1);
	}
	return (0);
}

int	apply_redirections(t_redirect *redirs)
{
	int	i;
	int	saved_stdin;
	int	saved_stdout;
	int	ret;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	i = 0;
	while (redirs && redirs[i].target)
	{
		ret = handle_single_redir(&redirs[i], &saved_stdin, &saved_stdout, &i);
		if (ret)
			return (ret);
		i++;
	}
	close(saved_stdin);
	close(saved_stdout);
	return (0);
}
