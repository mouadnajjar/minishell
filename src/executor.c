/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:36:02 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/02 16:38:50 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"
#include"../includes/executor.h"

int     execute_command(t_cmd *cmd, char **envp)
{
    pid_t   pid;

    pid = fork();
    if (pid == 0)
    {
        //checkmate
    }
    waitpid(pid, NULL, 0);
    return(0);
}