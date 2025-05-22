/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:09:18 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/21 14:11:10 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executor.h"

void	sigint_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);     // Clear the current input line
	rl_on_new_line();           // Move to new line
	rl_redisplay();             // Redisplay prompt
}

void	set_signals(void)
{
	signal(SIGINT, sigint_handler);  // Handle Ctrl+C
	signal(SIGQUIT, SIG_IGN);        // Ignore Ctrl+
}
