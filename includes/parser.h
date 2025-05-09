/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/05/09 15:52:08 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "libft.h"

typedef enum {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_IN,
    TOKEN_APPEND,
    TOKEN_HEREDOC,
	// TOKEN_QUOTE_SINGLE,
	// TOKEN_QUOTE_DOUBLE,
} t_token_type;

typedef struct s_token {
    char            *value;
    t_token_type    type;
    struct s_token  *next;
} t_token;

extern t_list *gc;

void    free_cmds(t_cmd *cmd);
int ft_isspace(int c);

//garbage
void *gc_malloc(t_list **gc, size_t size);
void gc_free_all(t_list **gc);

//parse_input
t_cmd *parser(t_token *tokens);
t_cmd *parse_input(const char *input);
int word_token(t_token *current, t_list **argv_list);
t_token *handle_word_token(const char *input, size_t *i);
int redirection_token(t_token **current, t_list **redir_list);
int finalize_cmd(t_cmd **current_cmd, t_list **argv_list, t_list **redir_list, t_cmd **head);
t_cmd *init_cmd(void);
char **list_to_argv(t_list *argv_list);
t_redir_type get_redir_type(t_token_type token_type);
void free_cmds(t_cmd *cmd);


//lexer
t_token *lexer(const char *input);
t_token *create_token(t_token_type type, const char *value, size_t len);
t_token *handle_special_token(const char *input, size_t *i);
size_t skip_whitespace(const char *input, size_t i);
t_redirect *list_to_redirs(t_list *redir_list);


#endif


