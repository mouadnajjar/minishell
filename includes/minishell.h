/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by monajjar          #+#    #+#             */
/*   Updated: 2025/07/02 22:14:53 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PROMPT "minishell$ "
# define GREEN_BOLD "\001\033[1;32m\002"
# define RESET "\001\033[0m\002"

typedef enum e_redir_type
{
	IN,
	OUT,
	TRUNCATE,
	APPEND,
	HEREDOC
}					t_redir_type;

typedef struct s_redirect
{
	char			*target;
	t_redir_type	type;
	int				heredoc_fd;
	int				quoted;
	int				ambiguous_redirect;
	char			*ambg_name;
}					t_redirect;

typedef struct s_cmd
{
	char			**argv;
	t_redirect		*redirs;
	int				redir_count;
	int				is_pipe;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_shell
{
	char			**envp;
	int				last_exit_status;
	t_list			*gc;
	pid_t			*pids;
	int				heredoc_sigint;
	int				ambiguous_redirect;
	char			*ambg_name;
}					t_shell;

extern t_shell		g_shell;

void				gc_free_all(void);

#endif
