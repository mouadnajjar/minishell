/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:17 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/03 12:21:45 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executor.h"

int main (int ac, char **av, char **envp)
{
    char    *input;
    char    **env_copy;
    (void)ac;
    (void)av;
    
    env_copy = copy_env(envp);
    while (1)
    {
        input = readline(PROMPT);
		if (!input)
        {
            write(1, "exit\n", 6);
            break ;
        }
        if (*input)
        {
            add_history(input);
            execute_command(input, env_copy);
        }
        free(input);
    }
    return (0);
}
