/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:17 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/02 12:21:33 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main (void)
{
    char    *input;
    
    while (1)
    {
        input = readline("Minishell$ ");
        if (!input)
        {
            write(1, "exit\n", 6);   
            break ;
        }
        if (*input)
            add_history(input);
        free(input);
    }
    return (0);
}