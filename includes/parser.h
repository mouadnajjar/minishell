/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/15 14:50:52 by ahlahfid         ###   ########.fr       */
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

#define MAX_HEREDOCS 16

typedef enum e_token_type {
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
    TOKEN_INVALID,
}	t_token_type;

typedef enum e_parse_error
{
	ERR_NONE = 0,
	ERR_UNCLOSED_QUOTE,
	ERR_UNEXPECTED_TOKEN,
	ERR_HEREDOC_DELIM,
	ERR_EMPTY_COMMAND,
	ERR_NEAR_NEWLINE,
	ERR_INVALID_TOKEN

}	t_parse_error;

typedef struct s_token {
	char			*value;
	t_token_type	type;
	bool			can_expand;
	bool		is_heredoc_delim;
    int             start_index;
    int             end_index;
}	t_token;

typedef struct s_gc_node {
	void				*ptr;
	struct s_gc_node	*next;
}	t_gc_node;

//GC
extern t_list *gc;

// === Memory Management (GC) ===
void	*gc_alloc(size_t size, t_list **gc);
char	*gc_strdup(const char *s, t_list **gc);
char	*gc_substr(const char *s, unsigned int start, size_t len, t_list **gc);
void	gc_add(void *ptr, t_list **gc);
void	gc_free_all(t_list **gc);

// === Tokenization & Parsing ===
t_list	*split_input(const char *input);
t_token	*extract_quoted(const char *input, size_t *i);
t_token	*extract_special(const char *input, size_t *i);
t_token	*extract_word(const char *input, size_t *i);
int		is_word_end(char c);
int		ft_isspace(char c);
int		is_special(const char *s);
int		is_quoted(const char *s);
int		split_word_token(const char *input, size_t *i, t_list **tokens);
int		split_special_token(const char *input, size_t *i, t_list **tokens);
int		split_quoted_token(const char *input, size_t *i, t_list **tokens);

// === Token Utilities ===
void	print_tokens(t_list *tokens);
void	print_cmds(t_cmd *cmd);
void	print_parse_error(t_parse_error code, char *c);

// === Command Building ===
t_cmd	*parse_input(const char *input);
t_cmd	*build_single_cmd(t_list **tokens);
t_cmd	*build_commands(t_list *tokens);
t_cmd	*init_cmd_struct(t_list **tokens);
int		count_args(t_list *tokens);
int		count_redirections(t_list *tokens);
int		add_redirection(t_redirect *redir, t_token *redir_op, t_token *target);
int		is_invalid_redir(const char *s);
int		is_valid_redirection(const char *s);
t_redir_type	get_redir_type(t_token_type type);

// === Command Parsing Helpers ===
int		handle_redirection_token(t_cmd *cmd, int *redir_i, t_list **tokens);
void	handle_word_token(t_cmd *cmd, char *value, int *arg_i);
int		handle_pipe_token(t_list **tokens, t_cmd *cmd);
int		parse_cmd_tokens(t_cmd *cmd, t_list **tokens, int *arg_i, int *redir_i);
int		check_pipe_start(t_list *tokens);

// === Token Merging ===
void	merge_adjacent_words(t_list **tokens, const char *input);
void	merge_tokens(t_list *curr, t_token *a, t_token *b);
int		has_no_space_between(t_token *a, t_token *b, const char *input);

// === Expansion ===
void	expand_tokens(t_list *tokens);
char	*expand_value(const char *src);
size_t	get_expanded_length(const char *src);
char	*get_env_var(const char *name);
char	*get_env_name(const char *src, size_t i, size_t *var_len);
size_t	get_expanded_var_len(const char *src, size_t *i);
size_t	get_exit_status_len(void);
void	copy_char(char *dst, const char *src, size_t *i, size_t *j);
void	append_dollar(char *dst, size_t *j);
void	expand_status(char *dst, size_t *j);
char	*get_var_name(const char *src, size_t i, size_t *out_len);
void	append_var_value(const char *name, char *dst, size_t *j);
void	handle_dollar_case(const char *src, size_t *i, char *dst, size_t *j);

// === Redirection & Heredoc ===
void	process_heredocs(t_cmd *cmds);
void	handle_heredoc(t_redirect *redir);
t_list	*extract_heredoc_delimiter(const char *input, size_t *i);
void	init_heredoc_pipe(int *fd);
int	count_heredocs(t_cmd *cmds);

// === Quoting Utilities ===
char	*remove_quotes(const char *str);
char	*alloc_quoted_value(const char *input, size_t start, size_t len, char quote);
size_t	get_quoted_length(const char *input, size_t *i, char quote);
t_token	*create_quoted_token(char *value, size_t start, size_t end, char quote);

// === Operator Utilities ===
t_token_type	get_operator_type(const char *op);
char	*get_operator(const char *input, size_t *i);
t_token_type	validate_and_get_type(char *op);
t_token	*alloc_word_token(const char *input, size_t start, size_t len);

#endif


