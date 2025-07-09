/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:51:29 by monajjar          #+#    #+#             */
/*   Updated: 2025/07/08 17:18:22 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/executor.h"
#include "./../includes/minishell.h"

int	is_valid_exit_code(const char *str)
{
	int	len;

	if (!str || !*str)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	len = ft_strlen(str);
	if (len >= 19)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static void	print_exit_message(const char *message)
{
	if (message)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		write(2, message, ft_strlen(message));
		ft_putendl_fd(": numeric argument required", 2);
	}
	g_shell.last_exit_status = 2;
	free_gc_memory();
	free_env(g_shell.envp);
}

static void	print_error_message(void)
{
	ft_putendl_fd("minishell: exit: too many arguments", 2);
	g_shell.last_exit_status = 1;
}

int	builtin_exit(char **args)
{
	long	exit_code;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (!args[1])
	{
		free_gc_memory();
		free_env(g_shell.envp);
		return (BUILTIN_EXIT);
	}
	if (!is_valid_exit_code(args[1]))
	{
		print_exit_message(args[1]);
		return (BUILTIN_EXIT);
	}
	if (args[2])
	{
		print_error_message();
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	free_gc_memory();
	free_env(g_shell.envp);
	g_shell.last_exit_status = exit_code % 256;
	return (BUILTIN_EXIT);
}
