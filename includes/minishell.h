/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/12 17:06:25 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// C standard libs
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>

//  Libft
# include "libft.h"

// System calls
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

// Readline
# include <readline/readline.h>
# include <readline/history.h>

// Prompt
# define PROMPT ">|"

typedef enum {
    IN,        // < (input redirection)
    OUT,       // > (output redirection)
	TRUNCATE, // > (output redirection in truncate mode)
    APPEND,    // >> (output redirection in append mode)
    HEREDOC    // << (here-doc)
} t_redir_type;

typedef struct s_redirect {
    char            *target;      // file or delimiter
    t_redir_type    type;
    int             quoted;       // HEREDOC: 1 if 'DELIM' or "DELIM"
    int             heredoc_fd;   // HEREDOC: fd to read content from
} t_redirect;

typedef struct s_cmd {
    char            **argv;     // Command and arguments
    t_redirect      *redirs;    // Array of redirections
	int			redir_count;  // ⚠️⚠️NEW added for the number of redirections
    int             is_pipe;    // Flag for pipe
    struct s_cmd    *next;      // Next command in pipeline
} t_cmd;

// new has been added for the expansion
typedef struct s_shell {
    char            **envp;          // Environment variables
    int             last_exit_status; // Exit status of last command
} t_shell;

extern t_shell g_shell; // Global shell state

char	*get_cmmand_path(char *cmd, char **envp);
void	execute_commands(t_cmd *cmd_list, char **envp);
char 	**copy_env(char **envp);

#endif
