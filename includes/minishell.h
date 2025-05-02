/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/02 12:49:33 by monajjar         ###   ########.fr       */
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

// Shared struct
typedef struct s_cmd {
    char			**argv;
    char			*infile;
    char			*outfile;
    int				append;
    int				is_pipe;
    struct s_cmd	*next;
} 					t_cmd;

#endif
