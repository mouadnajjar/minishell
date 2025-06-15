/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:17 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/15 16:07:44 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"

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
	update_shell_level(&g_shell.envp);
	initialize_env(&g_shell.envp);
	set_signals();
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
			execute_commands(cmds, &g_shell.envp);
		free(input);
	}
	gc_free_all(&gc);
	return (0);
}
