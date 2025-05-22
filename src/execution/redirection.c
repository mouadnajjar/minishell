/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:50:03 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/10 14:41:59 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executor.h"

void	handle_input_redir(char *file)
{
	int	fd;
	
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		exit(EXIT_FAILURE);
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
		exit(EXIT_FAILURE);
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
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_herdoc(char *delimiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ((ft_strlen(line) == ft_strlen(delimiter))
			&& (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)))
			break ;
		//if (line && *line)
			//add_history(line);
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free (line);
	}
	free(line);
	close (pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close (pipefd[0]);
}


void	apply_redirections(t_redirect *redirs)
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
		else if (redirs[i].type == HEREDOC)
			handle_herdoc(redirs[i].target);
		i++;
	}
}
