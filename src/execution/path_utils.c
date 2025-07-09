/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:51:40 by monajjar          #+#    #+#             */
/*   Updated: 2025/07/08 18:23:16 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"
#include "../../includes/parser.h"

void	update_last_arg_var(char ***envp, char **argv)
{
	int	i;

	i = 0;
	if (!argv || !argv[0])
		return ;
	while (argv[i])
		i++;
	update_env(envp, "_", argv[i - 1]);
}

char	**split_paths(char **envp)
{
	int	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

char	*get_cmmand_path(char *cmd, char **envp)
{
	t_path	c;

	if (ft_strchr(cmd, '/') && (access(cmd, X_OK) == 0))
		return (ft_strdup(cmd));
	if (ft_strchr(cmd, '/') && !(access(cmd, X_OK) == 0))
		return (NULL);
	c.paths = split_paths(envp);
	if (!c.paths)
		return (NULL);
	c.j = 0;
	while (c.paths[c.j])
	{
		c.full_path = ft_strjoin(c.paths[c.j], "/");
		c.path = ft_strjoin(c.full_path, cmd);
		free(c.full_path);
		if (access(c.path, X_OK) == 0)
		{
			free_2d_array(c.paths);
			return (c.path);
		}
		free(c.path);
		c.j++;
	}
	free_2d_array(c.paths);
	return (NULL);
}

static void	handle_path_command(char **argv, char **envp)
{
	struct stat	st;

	if (access(argv[0], F_OK) == 0)
	{
		if (stat(argv[0], &st) == 0 && S_ISDIR(st.st_mode))
			print_dir_not_found(argv[0], envp);
		if (access(argv[0], X_OK) != 0)
			print_permission_denied(argv[0], envp);
		try_exec_path(argv, envp);
	}
	else
		handle_path_error(argv[0], envp);
}

void	run_command(char **argv, char **envp)
{
	char	*cmd_path;
	char	*path_env;

	if (!argv || !argv[0] || !argv[0][0])
		exit_cmd_not_found(envp);
	if (ft_strchr(argv[0], '/'))
		handle_path_command(argv, envp);
	path_env = get_env_value(envp, "PATH");
	if (!path_env || !*path_env)
		try_exec_in_cwd(argv, envp);
	cmd_path = get_cmmand_path(argv[0], envp);
	if (!cmd_path)
		print_command_not_found(argv[0], envp);
	execve(cmd_path, argv, envp);
	execve_error(cmd_path);
}
