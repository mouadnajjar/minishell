/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:19:46 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/02 20:35:08 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/executor.h"

int	check_flag(char *cmd)
{
	int	i;

	if (!cmd || cmd[0] != '-' || cmd[1] != 'n')
		return (0);
	i = 2;
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (argv[i] && check_flag(argv[i]))
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		 if (argv[i + 1])
		 	write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}

int exec_echo(t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	if (ft_strncmp(cmd->argv[0], "echo", 4) == 0)
		return (builtin_echo(cmd->argv));
	return (1);
}
