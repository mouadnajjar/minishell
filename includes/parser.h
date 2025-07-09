/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/07/05 18:50:12 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "minishell.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define MAX_HEREDOCS 16
# define DOUBLE_QUOTES -2
# define SINGLE_QUOTES -1

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_INVALID,
}					t_token_type;

typedef enum e_parse_error
{
	ERR_NONE = 0,
	ERR_UNCLOSED_QUOTE,
	ERR_UNEXPECTED_TOKEN,
	ERR_HEREDOC_DELIM,
	ERR_EMPTY_COMMAND,
	ERR_NEAR_NEWLINE,
	ERR_INVALID_TOKEN,
	ERR_MAX_HEREDOCS_EXCEEDED,
}					t_parse_error;

typedef struct s_inc
{
	size_t			i;
	size_t			j;
}				t_inc;
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	bool			can_expand;
	bool			is_heredoc_delim;
	bool			from_expansion;
	int				start_index;
	int				end_index;
	int				ambiguous_redirect;
	char			*ambg_name;
	bool			quoted_2;
}					t_token;

typedef struct s_heredoc_extract
{
	size_t			start;
	size_t			curr;
	t_token			*token;
	char			quote_for_token;
	char			last_quote;
	int				has_quotes;
}					t_heredoc_extract;

/* ==========================================================
** Memory Management (GC)
** ========================================================== */

void				*gc_alloc(size_t size);
char				*gc_strdup(const char *s);
char				*gc_substr(const char *s, unsigned int start, size_t len);
void				gc_add(void *ptr);
char				**gc_split(char const *s);
size_t				gc_count_word(const char *str);

/* ==========================================================
** Input Splitting & Tokenization
** ========================================================== */

t_list				*split_input(char *input);

int					ft_isspace(char c);
int					is_special(const char *s);
int					is_quoted(const char *s);
int					is_word_end(char c);

int					split_word_token(const char *input, size_t *i,
						t_list **tokens);
int					split_special_token(char *input, size_t *i,
						t_list **tokens);
int					split_quoted_token(char *input, size_t *i, t_list **tokens);

/* ==========================================================
** Token Extraction
** ========================================================== */

t_token				*extract_word(const char *input, size_t *i);
t_token				*extract_special(const char *input, size_t *i);
t_token				*extract_quoted(char *input, size_t *i);
void				init_for_extract_special(t_token *token);
t_token				*alloc_word_token(const char *input, size_t start,
						size_t len);

/* ==========================================================
** Token Utilities & Printing
** ========================================================== */

// void	print_tokens(t_list *tokens);
// void	print_cmds(t_cmd *cmd);

void				print_parse_error(t_parse_error code, char *str);
void				unclosed_quote(char *str);
void				heredoc_delim(char *str);
void				unexpected_token(char *str);
void				near_newline(void);
void				empty_command(void);
void				max_heredocs_exceeded(void);

/* ==========================================================
** Quoting Utilities
** ========================================================== */

char				*remove_quotes(const char *str, t_token *tok);
char				*alloc_quoted_value(const char *input, size_t start,
						size_t len, char quote);
char				*alloc_quoted_value_heredoc(const char *input, size_t start,
						size_t len);
size_t				get_quoted_length(const char *input, size_t *i, char quote);
t_token				*create_quoted_token(char *value, size_t start, size_t end,
						char quote);
t_token				*create_quoted_token_heredoc(char *value, size_t start,
						size_t end, char quote);
int					is_quoted_origin(const char *s);

/* ==========================================================
** Operator Utilities
** ========================================================== */

t_token_type		get_operator_type(const char *op);
char				*get_operator(const char *input, size_t *i);
t_token_type		validate_and_get_type(char *op);

/* ==========================================================
** Command Parsing & Building
** ========================================================== */

t_cmd				*parse_input(char *input);
t_cmd				*build_single_cmd(t_list **tokens);
t_cmd				*build_commands(t_list *tokens);
t_cmd				*init_cmd_struct(t_list **tokens);

int					count_args(t_list *tokens);
int					count_token_args(t_token *tok);
int					count_redirections(t_list *tokens);
int					is_pipe_token(t_list *tokens);
int					is_word_token(t_list *tokens);

int					add_redirection(t_redirect *redir, t_token *redir_op,
						t_token *target);
int					is_invalid_redir(const char *s);
int					is_valid_redirection(const char *s);
t_redir_type		get_redir_type(t_token_type type);

/* ==========================================================
** Command Parsing Helpers
** ========================================================== */

int					handle_redirection_token(t_cmd *cmd, int *redir_i,
						t_list **tokens);
void				handle_word_token(t_cmd *cmd, t_token *tok, int *arg_i);
int					handle_pipe_token(t_list **tokens, t_cmd *cmd);
int					parse_cmd_tokens(t_cmd *cmd, t_list **tokens, int *arg_i,
						int *redir_i);
int					check_pipe_start(t_list *tokens);

/* ==========================================================
** Token Merging
** ========================================================== */

void				merge_adjacent_words(t_list **tokens, const char *input);
void				merge_tokens(t_list *curr, t_token *a, t_token *b);
int					has_no_space_between(t_token *a, t_token *b,
						const char *input);

/* ==========================================================
** Expansion
** ========================================================== */

void				expand_tokens(t_list *tokens);
char				*expand_value(const char *src, t_token *tok);
size_t				get_expanded_length(const char *src);
char				*get_env_var(const char *name);
char				*get_env_name(const char *src, size_t i, size_t *var_len);
size_t				get_expanded_var_len(const char *src, size_t *i);
size_t				get_exit_status_len(void);
void				copy_char(char *dst, const char *src, size_t *i, size_t *j);
void				append_dollar(char *dst, size_t *j);
void				expand_status(char *dst, size_t *j);
char				*get_var_name(const char *src, t_inc *inc, size_t *out_len);
void				append_var_value(const char *name, char *dst, size_t *j);
void				handle_dollar_case(const char *src, t_inc *inc,
						char *dst, t_token *tok);
size_t				dollar_sign_len(const char *src, size_t *i);
void				handle_variable_expansion(const char *src, t_inc *inc,
						char *dst, t_token *tok);

/* ==========================================================
** Redirection & Heredoc
** ========================================================== */

void				process_heredocs(t_cmd *cmds);
void				handle_heredoc(t_redirect *redir);
t_list				*extract_heredoc_delimiter(char *input, size_t *i);
void				init_heredoc_pipe(int *fd);
int					count_heredocs(t_cmd *cmds);
t_token				*extract_quoted_heredoc(char *input, size_t *i);
t_token				*build_heredoc_token(char *input, size_t start, size_t curr,
						char quote);

int					is_delimiter_or_eof(t_redirect *redir, char *line);
void				process_heredoc_line(t_redirect *redir, int write_fd,
						char *line);
void				handle_heredoc_child(t_redirect *redir, int *fd);
void				child_heredoc_loop(t_redirect *redir, int write_fd);
void				cleanup_heredoc(int *fd, char *line);
void				heredoc_ctrl_c(int sig);
void				handle_heredoc_parent(t_redirect *redir, int *fd,
						pid_t pid);
void				init_fd_sigint(t_redirect *redir);

#endif
