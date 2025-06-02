/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/02 12:35:11 by monajjar         ###   ########.fr       */
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

//  printf
# include "ft_printf.h"

// System calls
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

// Readline
# include <readline/readline.h>
# include <readline/history.h>

// Prompt
# define PROMPT "minishell$ "
# define GREEN_BOLD "\001\033[1;32m\002"
# define RESET      "\001\033[0m\002"

extern int	g_exit_status; // Global variable to store exit status

typedef enum {
    IN,        // < (input redirection)
    OUT,       // > (output redirection)
    APPEND,    // >> (output redirection in append mode)
    TRUNCATE, // > (output redirection in truncate mode)
    HEREDOC    // << (here-doc)
} t_redir_type;

typedef struct s_redirect {
    char            *target;    // File or delimiter (e.g., "file.txt" or "EOF")
    t_redir_type    type;     // Type of redirection (IN, OUT, APPEND, HEREDOC)
    int             fd;
} t_redirect;

typedef struct s_cmd {
    char            **argv;     // Command and arguments
    t_redirect      *redirs;    // Array of redirections
    int             is_pipe;    // Flag for pipe
    struct s_cmd    *next;      // Next command in pipeline
} t_cmd;

//-------------------------execution-> implement-----------------------//
char	*get_cmmand_path(char *cmd, char **envp);
void	execute_commands(t_cmd *cmd_list, char ***envp);
#endif
