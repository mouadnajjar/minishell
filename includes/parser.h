/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/05/22 13:43:04 by ahlahfid         ###   ########.fr       */
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
#include <fcntl.h>
#include <stdbool.h>
#include <errno.h>
#include "libft.h"


typedef enum {
    TOKEN_WORD, //0
    TOKEN_PIPE, //1
    TOKEN_REDIR_OUT, //2
    TOKEN_REDIR_IN, //3
    TOKEN_APPEND, //4
    TOKEN_HEREDOC, //5
    TOKEN_QUOTE_SINGLE, //6
    TOKEN_QUOTE_DOUBLE, //7
    //TOKEN_VARIABLE // New token type for variables
} t_token_type;

typedef struct s_token {
    char            *value;
    t_token_type    type;
    struct s_token  *next;
} t_token;

extern t_list *gc;

void	free_cmds(t_cmd *cmd);
int		ft_isspace(int c);

//garbage
void	*gc_malloc(t_list **gc, size_t size);
void	gc_free_all(t_list **gc);

//parse_input
t_cmd	*parser(t_token *tokens);
t_cmd	*parse_input(const char *input);
int		word_token(t_token *current, t_list **argv_list);
t_token	*handle_word_token(const char *input, size_t *i);
int		redirection_token(t_token **current, t_list **redir_list);
int		finalize_cmd(t_cmd **current_cmd, t_list **argv_list, t_list **redir_list, t_cmd **head);
t_cmd	*init_cmd(void);
char	**list_to_argv(t_list *argv_list);
t_redir_type	get_redir_type(t_token_type token_type);
void	free_cmds(t_cmd *cmd);



//lexer
t_token	*lexer(const char *input);
t_token	*create_token(t_token_type type, const char *value, size_t len);
t_token *handle_special_token(const char *input, size_t *i);
size_t	skip_whitespace(const char *input, size_t i);
t_redirect	*list_to_redirs(t_list *redir_list);
bool is_quote(char c);

//expand
char	*get_env_var(char **envp, const char *var);
char	*expand_variables(const char *str);
size_t	handle_quoted_dollar(const char *str, size_t *i);
char	*extract_var_name(const char *str, size_t *i, int braced_flag);
size_t	get_var_length(char *var);
size_t	compute_expanded_length(const char *str);
size_t	handle_dollar_expansion(const char *str, size_t *i);
void	handle_exit_status(char **result, size_t *j);
void	handle_braced_variable(const char *str, size_t *i, char **result, size_t *j);
void	handle_unbraced_variable(const char *str, size_t *i, char **result,
	size_t *j);
void	handle_dollar(const char *str, size_t *i, char **result, size_t *j);
size_t ft_numlen(int num);

//debug
const char *redir_type_to_str(t_redir_type type);



#endif


