/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:09:18 by monajjar          #+#    #+#             */
/*   Updated: 2025/07/05 12:59:09 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"

void	handle_sigint_output(t_wait *w, int cmd_counts)
{
	if (WIFSIGNALED(w->status) && WTERMSIG(w->status) == SIGINT
		&& cmd_counts > 1 && w->entred == 0)
	{
		w->entred = 1;
		write(1, "\n", 1);
	}
}

void	set_default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	g_shell.last_exit_status = 0;
}

void	sigint_handler(int signum)
{
	(void)signum;
	if (waitpid(-1, NULL, WNOHANG) == 0)
		return ;
	g_shell.last_exit_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	free_all(void)
{
	free_gc_memory();
	if (g_shell.envp)
		free_env(g_shell.envp);
}
