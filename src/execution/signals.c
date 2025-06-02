/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:09:18 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/02 14:08:02 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executor.h"

void sigint_handler(int signum)
{
    (void)signum;
    if (waitpid(-1, NULL, WNOHANG) == 0) // Check if a child process is running
        return; // Do not redisplay the prompt if a child process is running

    g_exit_status = 130;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void sigquit_handler(int signum)
{
    (void)signum;

    // Check if a child process is running
    if (waitpid(-1, NULL, WNOHANG) == 0) // A child process is running
    {
        write(STDOUT_FILENO, "Quit: 3\n", 8); // Display the message like Bash
    }
    else
    {
        // No foreground process is running, ignore the signal
        return;
    }
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void	set_signals(void)
{
	signal(SIGINT, sigint_handler);  // Handle Ctrl+C
	signal(SIGQUIT, SIG_IGN);        // Ignore Ctrl+
}
