/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:17 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/20 15:01:57 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/executor.h"

t_list *gc = NULL;
t_shell g_shell;

int main(int ac, char **av, char **envp)
{
    char    *input;
    char    **env_copy;
    t_cmd   *cmds;
	char	*prompt;
    (void)ac;
    (void)av;

	prompt = PROMPT;

	env_copy = NULL;
    g_shell.envp = copy_env(envp);
	printf("=== Environment Variables ===\n");
	//for (int i = 0; g_shell.envp[i]; i++)
	//	printf("%s\n", g_shell.envp[i]);
	printf("=== End of Environment Variables ===\n");

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

       cmds = parse_input(input);

	   execute_commands(cmds, g_shell.envp);     // run your real executor
	   free(input);
    }
	free_env(g_shell.envp);
    return (0);
}
