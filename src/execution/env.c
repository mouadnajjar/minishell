/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:07:22 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/15 14:43:42 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"

void	update_shell_level(char ***envp)
{
	char	*shell_level;
	char	*new_shell_level;
	int		level;

	shell_level = get_env_value(*envp, "SHLVL");
	if (!shell_level)
		level = 1;
	else
		level = ft_atoi(shell_level) + 1;
	if (level < 0)
		level = 0;
	new_shell_level = ft_itoa(level);
	update_env(envp, "SHLVL", new_shell_level);
	free(new_shell_level);
}

char	**copy_env(char **envp)
{
	char	**new_env;
	size_t	i;

	i = 0;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	initialize_env(char ***envp)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		update_env(envp, "PWD", cwd);
		free(cwd);
	}
	else
	{
		update_env(envp, "PWD", "/");
	}
	update_env(envp, "_", "/home/monajjar/Desktop/minishelll/./minishell");
}
