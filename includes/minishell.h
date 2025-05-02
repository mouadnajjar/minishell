/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/02 09:57:00 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

enum{
    a,
    b,
    PIPE,
};

typedef struct s_list
{
    char			*conetent;
    int				type;
    char			**args;
    char			*in;
    char			*out;
    struct s_list	*next;
}                   t_list;

#endif
