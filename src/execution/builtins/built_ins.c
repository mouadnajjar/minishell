/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:23:58 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/22 17:00:17 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/executor.h"

int exec_builtins(t_cmd *cmd, char ***env)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	if (ft_strncmp(cmd->argv[0], "echo", 4) == 0)
		return (builtin_echo(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "pwd", 3) == 0)
		return (get_pwd());
	if (ft_strncmp(cmd->argv[0], "cd", 2) == 0)
		return (builtin_cd(cmd->argv, env));
	if (ft_strncmp(cmd->argv[0], "export", 6) == 0)
		return (builtin_export(cmd->argv, env));
	if (ft_strncmp(cmd->argv[0], "unset", 5) == 0)
		return (builtin_unset(cmd->argv, env));
	if (ft_strncmp(cmd->argv[0], "env", 3) == 0)
		return (builtin_env(cmd->argv, *env));                                                                                                         
	return (0);
}
