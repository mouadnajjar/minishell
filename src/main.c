/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:17 by monajjar          #+#    #+#             */
/*   Updated: 2025/07/05 16:56:51 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"

t_shell		g_shell;

static void	setup_env(char **envp)
{
	g_shell.envp = copy_env(envp);
	g_shell.last_exit_status = 0;
}

static void	handle_exit(void)
{
	write(1, "exit\n", 5);
	gc_free_all();
	free_env(g_shell.envp);
}

static void	init_shell(char **envp)
{
	setup_env(envp);
	update_shell_level(&g_shell.envp);
	initialize_env(&g_shell.envp);
	set_signals();
}

static void	voiding_args(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_cmd	*cmds;
	char	*prompt;

	voiding_args(argc, argv);
	prompt = GREEN_BOLD PROMPT RESET;
	init_shell(envp);
	while (1)
	{
		input = readline(prompt);
		if (!input)
		{
			handle_exit();
			break ;
		}
		if (*input)
			add_history(input);
		cmds = parse_input(input);
		if (cmds)
			execute_commands(cmds, &g_shell.envp);
		free(input);
	}
	gc_free_all();
	return (g_shell.last_exit_status);
}
