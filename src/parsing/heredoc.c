/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/15 15:02:32 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

int	count_heredocs(t_cmd *cmds)
{
	int			count;
	t_redirect	*r;
	int			i;

	count = 0;
	while (cmds)
	{
		r = cmds->redirs;
		i = 0;
		while (r && r[i].target)
		{
			if (r[i].type == HEREDOC)
				count++;
			i++;
		}
		cmds = cmds->next;
	}
	return (count);
}

void	process_heredocs(t_cmd *cmds)
{
	t_redirect	*r;
	int			i;
	int			heredoc_count;

	heredoc_count = count_heredocs(cmds);
	if (heredoc_count > MAX_HEREDOCS)
	{
		ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
		gc_free_all(&gc);
		exit(2);
	}
	while (cmds)
	{
		r = cmds->redirs;
		i = 0;
		while (r && r[i].target)
		{
			if (r[i].type == HEREDOC)
				handle_heredoc(&r[i]);
			i++;
		}
		cmds = cmds->next;
	}
}

void	init_heredoc_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("minishell: pipe");
		gc_free_all(&gc);
		exit(1);
	}
}

void	handle_heredoc(t_redirect *redir)
{
	char	*line;
	char	*expanded;
	int		fd[2];

	init_heredoc_pipe(fd);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_parse_error(ERR_HEREDOC_DELIM, redir->target);
			break ;
		}
		if (ft_strncmp(line, redir->target, ft_strlen(redir->target) + 1) == 0
			&& (ft_strlen(line) == ft_strlen(redir->target)))
			break ;
		if (redir->quoted == 0)
			expanded = expand_value(line);
		else
			expanded = gc_strdup(line, &gc);
		write(fd[1], expanded, ft_strlen(expanded));
		write(fd[1], "\n", 1);
	}
	close(fd[1]);
	redir->heredoc_fd = fd[0];
}

t_list	*extract_heredoc_delimiter(const char *input, size_t *i)
{
	t_token	*next;
	t_list	*node;

	next = NULL;
	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
	if (input[*i] == '\'' || input[*i] == '"')
		next = extract_quoted(input, i);
	else if (!is_special(input + *i) && input[*i] != '\0')
		next = extract_word(input, i);
	if (!next)
		return (NULL);
	next->is_heredoc_delim = 1;
	node = ft_lstnew(next);
	gc_add(node, &gc);
	return (node);
}
