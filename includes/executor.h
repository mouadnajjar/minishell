/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:54:44 by monajjar          #+#    #+#             */
/*   Updated: 2025/07/08 18:10:47 by ahlahfid         ###   ########.fr       */
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
	int		i;
}			t_exec_ctx;

typedef struct s_wait
{
	int	i;
	int	status;
	int	sig;
	int	entred;
}		t_wait;
//------------------------------------------------//

typedef struct s_saved
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;
}			t_saved;

# define BUILTIN_EXIT 4242

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
void		set_default_signals(void);
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
int			is_directory(char *pathdir);
void		execve_error(char *cmd_path);
void		handle_command_list(t_cmd *cmd_list, t_exec_ctx *ctx, int *i);
int			check_heredoc(t_redirect	*redirs, int *i);
int			restore_fds(int saved_stdin, int saved_stdout);
int			handle_single_redir(t_redirect *redir, int *saved_stdin,
				int *saved_stdout, int *i);
void		handle_append_redir(char *file);
void		handle_output_redir(char *file);
void		handle_input_redir(char *file);
int			check_ambiguous(t_redirect *redirs);
void		handle_sigint_output(t_wait *w, int cmd_counts);
void		handle_path_error(char *cmd, char **envp);
void		exit_cmd_not_found(char **envp);
void		cleanup_heredoc_fds(t_redirect *redirs);
void		try_exec_path(char **argv, char **envp);
void		try_exec_in_cwd(char **argv, char **envp);
void		update_last_arg_var(char ***envp, char **argv);
void		print_permission_denied(char *cmd, char **envp);
void		print_dir_not_found(char *path, char **envp);
void		print_command_not_found(char *cmd, char **envp);
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
void		free_gc_memory(void);
void		set_and_free(void);
int			check_heredoc_and_clean(void);
void		free_all(void);
//-------------------------------------------------//

#endif
