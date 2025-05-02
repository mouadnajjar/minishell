/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/05/02 15:47:51 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
# define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "include/libft.h"

// typedef struct s_cmd
// {
//     char    **args;
//     int     pipe;
//     struct s_cmd *next;
// }   t_cmd;


t_cmd   *parse_input(const char *input);
void    free_cmds(t_cmd *cmd);


void gc_malloc(void *ptr);
void gc_free(void *ptr);

#endif


