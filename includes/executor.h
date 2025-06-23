/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:54:44 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/19 18:42:38 by monajjar         ###   ########.fr       */
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
	char	*old_path;
	int		j;
}			t_path;

typedef struct s_exec_ctx
{
	int		pipefd[2];
	int		prev_fd;
	char	**envp;
}			t_exec_ctx;
//------------------------------------------------//

//---------------execution-fucntions--------------//
void		run_command(char **argv, char **envp);
int			apply_redirections(t_redirect *redirs);
char		**copy_env(char **envp);
void		handle_export_assigment(char *arg, char ***env);
void		update_shell_level(char ***envp);
//------------------------------------------------//

//---------------exits--signals-------------------//
void		set_signals(void);
void		sigint_handler(int signum);
//------------------------------------------------//

//---------------------HELPERS--------------------//
int			getsize(t_cmd *lst);
void		wait_pids(pid_t *pids, int cmd_counts);
pid_t		*allocate_pid(int size);
int			close_and_update_pipe(t_cmd *cmd, int prev_fd, int pipefd[2]);
char		*ft_strjoin_3(const char *s1, const char *s2, const char *s3);
int			check_null(char *str, char *msg);
int			check_arguments_cd(char **argv);
char		*get_cd_path(char **argv, char ***env);
int			change_directory(char *path);
void		update_cd_env(char ***env, char *oldpwd);
int			env_len(char **env);
void		print_export_error(char *arg);
char		*get_cmmand_path(char *cmd, char **envp);
void		execute_commands(t_cmd *cmd_list, char ***envp);
void		init_execution_context(t_exec_ctx *ctx, char ***envp);
void		process_command(t_cmd *cmd_list, pid_t *pids, int i,
	t_exec_ctx *ctx);
void		fork_and_exec_command(t_cmd *cmd_list, pid_t *pids, int i,
		t_exec_ctx *ctx);
//-----------------------------------------------//

//------------------built-in---------------------//
int			is_built_in(char *line);
int			exec_builtins(t_cmd *cmd, char ***env);
int			builtin_echo(char **argv);
int			get_pwd(char **env);
int			builtin_cd(char **argv, char ***env);
int			ft_realloc_env(char ***env, char *new_var);
void		update_env(char ***env, char *key, char *value);
char		*get_env_value(char **env, const char *key);
int			builtin_export(char **argv, char ***env);
int			builtin_unset(char **argv, char ***env);
int			builtin_env(char **argv, char **env);
int			builtin_exit(char **args);
void		initialize_env(char ***envp);
//-----------------------------------------------//
//--------------------memmory-free-----------------//
void		free_env(char **env);
void		free_2d_array(char **arr);
void		free_env_allocation(int i, char **env, char *var);
void		free_gc_memory();
//-------------------------------------------------//

#endif
