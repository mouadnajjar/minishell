/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:51:40 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/20 13:42:47 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"
#include"../../includes/executor.h"

char	**split_paths(char **envp)
{
	int		i;
	char	*default_path;

	default_path = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";
	if (!envp)
		return (ft_split(default_path, ':'));
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (ft_split(default_path, ':'));
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
		free (c.path);
		c.j++;
	}
	free_2d_array(c.paths);
	return (NULL);
}

void	run_command(char **argv, char **envp)
{
	char	*cmd_path;
	
	if (!argv || !argv[0])
	{
		ft_putstr_fd("minishell : empty command\n", 2);
		exit (EXIT_FAILURE);
	}
	cmd_path = get_cmmand_path(argv[0], envp);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell : comnmand not found :", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd("\n", 2);
		exit (127);
	}
	execve(cmd_path, argv, envp);
	perror("execve");
	free(cmd_path);
	exit(EXIT_FAILURE);
}
