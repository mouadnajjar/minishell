/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:51:40 by monajjar          #+#    #+#             */
/*   Updated: 2025/07/08 18:11:25 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"

void	print_dir_not_found(char *path, char **envp)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	free_env(envp);
	free_gc_memory();
	exit(126);
}

void	print_command_not_found(char *cmd, char **envp)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	free_env(envp);
	free_gc_memory();
	exit(127);
}

void	print_permission_denied(char *cmd, char **envp)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	free_env(envp);
	free_gc_memory();
	exit(126);
}

void	handle_path_error(char *cmd, char **envp)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_env(envp);
	free_gc_memory();
	exit(127);
}

void	exit_cmd_not_found(char **envp)
{
	ft_putstr_fd("minishell: : command '' not found\n", 2);
	free_env(envp);
	free_gc_memory();
	exit(127);
}
