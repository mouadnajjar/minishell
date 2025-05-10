/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:17 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/10 15:43:54 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executor.h"


static t_redirect *parse_redirection(char **args)
{
	t_redirect	*redirs = malloc(sizeof(t_redirect) * 10); // max 10 redirs
	int			i = 0, j = 0;

	while (args[i])
	{
		if ((strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0 ||
			 strcmp(args[i], "<") == 0 || strcmp(args[i], "<<") == 0) && args[i + 1])
		{
			redirs[j].target = strdup(args[i + 1]);

			if (strcmp(args[i], ">>") == 0)
				redirs[j].type = APPEND;
			else if (strcmp(args[i], ">") == 0)
				redirs[j].type = TRUNCATE;
			else if (strcmp(args[i], "<") == 0)
				redirs[j].type = IN;
			else
				redirs[j].type = HEREDOC;

			args[i][0] = '\0';        // mark as removed
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
	redirs[j].target = NULL; // end marker
	return (redirs);
}



static char **clean_args(char **args)
{
	int	i = 0, j = 0;
	int	len = 0;

	// First count how many valid args
	while (args[len])
		len++;

	char **cleaned = malloc(sizeof(char *) * (len + 1));
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
	char	**segments = ft_split(input, '|');
	t_cmd	*head = NULL;
	t_cmd	*curr = NULL;
	int		i = 0;

	while (segments && segments[i])
	{
		t_cmd	*node = malloc(sizeof(t_cmd));
		char	**args = ft_split(segments[i], ' ');
		node->redirs = parse_redirection(args);
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

int main(int ac, char **av, char **envp)
{
    char    *input;
    char    **env_copy;
    t_cmd   *cmds;
	char	*prompt;
    (void)ac;
    (void)av;
    
	prompt = GREEN_BOLD PROMPT RESET;
    env_copy = copy_env(envp);
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
       cmds = parse_simple_input(input); // use your fake parser
	   execute_commands(cmds, envp);     // run your real executor         
	   free(input);
    }
	free_env(env_copy);
    return (0);
}
