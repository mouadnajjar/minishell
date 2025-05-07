/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:36:02 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/03 14:05:01 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"
#include"../../includes/executor.h"

void     execute_command(char *cmd, char **envp)
{
    char    **args;
    char    *cmd_path;
    int     status;
    pid_t   pid;

    args = ft_split(cmd, ' ');
    if (!args || !args[0])
        return ;
    cmd_path = get_cmmand_path(args[0], envp);
    if (!cmd_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(args[0], 2);
		free_2d_array(args);
		return ;
	}
    pid = fork();
    if (pid == 0)
    {
        execve(cmd_path, args, envp);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, &status, 0);
    }
    free(cmd_path);
    free_2d_array(args);
}