/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_executor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:07:18 by monajjar          #+#    #+#             */
/*   Updated: 2025/07/08 18:17:11 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"

void	cleanup_heredoc_fds(t_redirect *redirs)
{
	int	j;

	j = 0;
	while (redirs && redirs[j].target)
	{
		if (redirs[j].type == HEREDOC && redirs[j].heredoc_fd != -1)
		{
			close(redirs[j].heredoc_fd);
			redirs[j].heredoc_fd = -1;
		}
		j++;
	}
}

void	try_exec_path(char **argv, char **envp)
{
	if (access(argv[0], X_OK) == 0)
	{
		execve(argv[0], argv, envp);
		execve_error(argv[0]);
	}
	else
		handle_path_error(argv[0], envp);
}

void	try_exec_in_cwd(char **argv, char **envp)
{
	if (access(argv[0], X_OK) == 0)
	{
		execve(argv[0], argv, envp);
		execve_error(argv[0]);
	}
}
