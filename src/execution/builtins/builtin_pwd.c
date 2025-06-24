/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:20 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/24 15:58:40 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"
#include "../../../includes/minishell.h"

int	get_pwd(char **env)
{
	char	*cwd;

	(void)env;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putendl_fd("cd: error retrieving current directory:", 2);
		ft_putstr_fd(" getcwd: cannot access parent directories:", 2);
		ft_putendl_fd(" No such file or directory", 2);
		g_shell.last_exit_status = 1;
		return (1);
	}
	ft_putendl_fd(cwd, 1);
	free(cwd);
	g_shell.last_exit_status = 0;
	free_gc_memory();
	return (0);
}
