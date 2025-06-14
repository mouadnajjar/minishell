/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:17 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/14 17:32:31 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"
#include "../includes/minishell.h"

t_redirect	*parse_redirection(char **args)
{
	int	i = 0, j;
	int	pipefd[2];

	t_redirect *redirs = malloc(sizeof(t_redirect) * 10);
		// assume max 10 redirs
	i = 0, j = 0;
	while (args[i])
	{
		if ((ft_strncmp(args[i], "<<", 2) == 0) && args[i + 1])
		{
			pipe(pipefd);
			write(pipefd[1], "line1 from heredoc\nline2\n", 26);
			close(pipefd[1]);
			redirs[j].type = HEREDOC;
			redirs[j].target = NULL;
			redirs[j].fd = pipefd[0];
			args[i][0] = '\0';
			args[i + 1][0] = '\0';
			j++;
			i++;
		}
		else if ((ft_strncmp(args[i], "<", 1) == 0) && args[i + 1])
		{
			redirs[j].type = IN;
			redirs[j].target = ft_strdup(args[i + 1]);
			redirs[j].fd = -1;
			args[i][0] = '\0';
			args[i + 1][0] = '\0';
			j++;
			i++;
		}
		else if ((ft_strncmp(args[i], ">>", 2) == 0) && args[i + 1])
		{
			redirs[j].type = APPEND;
			redirs[j].target = ft_strdup(args[i + 1]);
			redirs[j].fd = -1;
			args[i][0] = '\0';
			args[i + 1][0] = '\0';
			j++;
			i++;
		}
		else if ((ft_strncmp(args[i], ">", 1) == 0) && args[i + 1])
		{
			redirs[j].type = TRUNCATE;
			redirs[j].target = ft_strdup(args[i + 1]);
			redirs[j].fd = -1;
			args[i][0] = '\0';
			args[i + 1][0] = '\0';
			j++;
			i++;
		}
		i++;
	}
	if (j == 0)
	{
		free(redirs);
		return (NULL);
	}
	// Sentinel to mark end
	redirs[j].type = -1;
	redirs[j].target = NULL;
	redirs[j].fd = -1;
	return (redirs);
}

static char	**clean_args(char **args)
{
	int		i = 0, j;
	int		len;
	char	**cleaned;

	i = 0, j = 0;
	len = 0;
	// First count how many valid args
	while (args[len])
		len++;
	cleaned = malloc(sizeof(char *) * (len + 1));
	if (!cleaned)
		return (NULL);
	while (args[i])
	{
		if (args[i][0] != '\0')
			cleaned[j++] = strdup(args[i]);
		i++;
	}
	cleaned[j] = NULL;
	return (cleaned);
}

t_cmd	*parse_simple_input(char *input)
{
	char	**segments;
	t_cmd	*head;
	t_cmd	*curr;
	int		i;
	t_cmd	*node;
	char	**args;

	segments = ft_split(input, '|');
	head = NULL;
	curr = NULL;
	i = 0;
	while (segments && segments[i])
	{
		node = malloc(sizeof(t_cmd));
		args = ft_split(segments[i], ' ');
		node->redirs = parse_redirection(args); // ⬅️ handles heredocs here
		node->argv = clean_args(args);
		free_2d_array(args);
		node->is_pipe = segments[i + 1] != NULL;
		node->next = NULL;
		if (!head)
			head = node;
		else
			curr->next = node;
		curr = node;
		i++;
	}
	free_2d_array(segments);
	return (head);
}

int			g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**env_copy;
	t_cmd	*cmds;
	char	*prompt;

	(void)ac;
	(void)av;
	prompt = GREEN_BOLD PROMPT RESET;
	env_copy = copy_env(envp);
	update_shell_level(&env_copy);
	set_signals();
	while (1)
	{
		input = readline(prompt);
		if (!input)
		{
			write(1, "exit\n", 6);
			break ;
		}
		if (*input)
			add_history(input);
		cmds = parse_simple_input(input);  // fake parser
		execute_commands(cmds, &env_copy); // real executor
		free(input);
	}
	free_env(env_copy);
	return (g_exit_status);
}
