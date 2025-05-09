/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:54:44 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/09 17:18:31 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

//----------------structs-needed------------------//
typedef struct s_path
{
	char	**paths;
	char	*path;
	char	*full_path;
	int		j;
}			t_path;

typedef struct s_exec_ctx
{
	int		pipefd[2];
	int		prev_fd;
	char	**envp;
}	t_exec_ctx;
//------------------------------------------------//

//---------------execution-fucntions--------------//
void	run_command(char **argv, char **envp);
void	apply_redirections(t_redirect *redirs);
char    **copy_env(char **envp);
//------------------------------------------------//


//---------------------HELPERS--------------------//
int		getsize(t_cmd *lst);
void    wait_pids (pid_t *pids, int cmd_counts);
pid_t 	*allocate_pid(int size);
int		close_and_update_pipe(t_cmd *cmd, int prev_fd, int pipefd[2]);
//-----------------------------------------------//

//------------------built-in---------------------//
int	is_built_in(char *line);
int exec_echo(t_cmd *cmd);
//-----------------------------------------------//
//--------------------memmory-free-----------------//
void    free_env(char **env);
void	free_2d_array(char **arr);
//-------------------------------------------------//

#endif
