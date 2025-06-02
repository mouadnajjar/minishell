/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:17 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/02 14:52:52 by ahlahfid         ###   ########.fr       */
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
    t_cmd   *cmds;
    char    *prompt;

    (void)ac;
    (void)av;

    prompt = PROMPT;
    g_shell.envp = copy_env(envp);  // Allocate envp without gc_malloc

    // Optional debug: print env
    printf("=== Environment Variables ===\n");
    for (int i = 0; g_shell.envp[i]; i++)
        printf("%s\n", g_shell.envp[i]);
    printf("=== End of Environment Variables ===\n");

    while (1)
    {
        input = readline(prompt);
        if (!input)
        {
            write(1, "exit\n", 5);
            gc_free_all(&gc);          // 🚨 Cleanup memory from gc_malloc
            free_env(g_shell.envp);    // 🚨 Cleanup copied envp
            break;
        }

        if (*input)
            add_history(input);

        cmds = parse_input(input);
        if (cmds)
            execute_commands(cmds, g_shell.envp);
        else
        {
            ft_putstr_fd("minishell: nothing to execute\n", 2);
        }

        free(input);            // Free readline input
        gc_free_all(&gc);       // 🚨 Free memory from this iteration
    }

    return (0);
}
