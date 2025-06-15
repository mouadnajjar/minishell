/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/15 16:07:39 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// C standard libs
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// Libft
# include "libft.h"

// printf
# include "ft_printf.h"

// System calls
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

// Readline
# include <readline/history.h>
# include <readline/readline.h>

// Prompt
# define PROMPT "minishell$ "
# define GREEN_BOLD "\001\033[1;32m\002"
# define RESET "\001\033[0m\002"

// Global variable to store exit status


// Enum for redirection types
typedef enum e_redir_type
{
	IN,// < (input redirection)
	OUT,// > (output redirection)
	TRUNCATE,// > (output redirection in truncate mode)
	APPEND,// >> (output redirection in append mode)
	HEREDOC// << (here-doc)
} t_redir_type;
// Struct for redirection
typedef struct	s_redirect
{
	char			*target;// File or delimiter (e.g., "file.txt" or "EOF")
	t_redir_type	type;// Type of redirection (IN, OUT, APPEND, HEREDOC)
	int				heredoc_fd;// File descriptor
	int             quoted;
}	t_redirect;

// Struct for command
typedef struct s_cmd
{
	char			**argv;// Command and arguments
	t_redirect		*redirs;// Array of redirections
	int			redir_count;
	int				is_pipe;// Flag for pipe
	struct s_cmd	*next;// Next command in pipeline
}	t_cmd;

typedef struct s_shell {
    char            **envp;          // Environment variables
    int             last_exit_status; // Exit status of last command
} t_shell;

extern t_shell g_shell; // Global shell state
// Execution functions
char	*get_cmmand_path(char *cmd, char **envp);
void	execute_commands(t_cmd *cmd_list, char ***envp);

#endif
