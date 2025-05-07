/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:50:03 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/07 16:16:02 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executor.h"

void	redirect_input(char *infile)
{
	int	fd;

	fd = open (infile, O_RDONLY);
	if (fd < 0)
	{
		perror("open infile");
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redirect_output(char *outfile, int type)
{
	int	flags;
	int	fd;

	if (type == 2)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else if (type == 3)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(outfile, flags, 0644);
	if (fd < 0)
	{
		perror("open outfile");
		exit (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

