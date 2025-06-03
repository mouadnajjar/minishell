/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:17 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/03 21:00:43 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/executor.h"

t_list	*gc = NULL;
t_shell	g_shell;

static void	setup_env(char **envp)
{
	g_shell.envp = copy_env(envp);
	g_shell.last_exit_status = 0;
}

static void	handle_exit(void)
{
	write(1, "exit\n", 5);
	gc_free_all(&gc);
	free_env(g_shell.envp);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_cmd	*cmds;

	(void)argc;
	(void)argv;
	setup_env(envp);

	while (1)
	{
		input = readline(PROMPT);
		if (!input)
		{
			handle_exit();
			break;
		}
		if (*input)
			add_history(input);

		cmds = parse_input(input);
		if (cmds)
			execute_commands(cmds, g_shell.envp);
		free(input);
	}
	return (0);
}
