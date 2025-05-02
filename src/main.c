/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:17 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/02 16:51:20 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executor.h"

int main (int ac, char **av, char **envp)
{
    char    *input;
    (void)ac;
    (void)av;
    while (1)
    {
        input = readline(PROMPT);
        if (!input)
        {
            write(1, "exit\n", 6);   
            break ;
        }
        if (*input)
            add_history(input);
        free(input);
    }
    char **check = copy_env(envp);
    
    for (int i = 0; check[i]; i++)
    {
        printf("%s\n", check[i]);
    }
    return (0);
}