/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/14 20:29:57 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

int	split_word_token(const char *input, size_t *i, t_list **tokens)
{
	t_token	*token;
	t_list	*node;

	token = extract_word(input, i);
	if (token)
	{
		node = ft_lstnew(token);
		gc_add(node, &gc);
		ft_lstadd_back(tokens, node);
	}
	return (0);
}

int	split_special_token(const char *input, size_t *i, t_list **tokens)
{
	t_token	*token;
	t_list	*node;
	t_list	*hd_node;

	token = extract_special(input, i);
	if (!token)
		return (1);
	node = ft_lstnew(token);
	gc_add(node, &gc);
	ft_lstadd_back(tokens, node);
	if (token->type == TOKEN_HEREDOC)
	{
		hd_node = extract_heredoc_delimiter(input, i);
		if (hd_node)
			ft_lstadd_back(tokens, hd_node);
	}
	return (0);
}

int	split_quoted_token(const char *input, size_t *i, t_list **tokens)
{
	t_token	*token;
	t_list	*node;

	token = extract_quoted(input, i);
	if (!token && g_shell.last_exit_status == 2)
		return (1);
	if (token)
	{
		node = ft_lstnew(token);
		gc_add(node, &gc);
		ft_lstadd_back(tokens, node);
	}
	return (0);
}

t_list	*split_input(const char *input)
{
	t_list	*tokens;
	size_t	i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (input[i] == '\'' || input[i] == '"')
		{
			if (split_quoted_token(input, &i, &tokens))
				return (NULL);
		}
		else if (is_special(input + i))
		{
			if (split_special_token(input, &i, &tokens))
				return (NULL);
		}
		else
			split_word_token(input, &i, &tokens);
	}
	return (tokens);
}

// t_list	*split_input(const char *input)
// {
// 	t_list	*tokens = NULL;
// 	t_token	*token;
// 	size_t	i = 0;
// 	t_list *node;

// 	while (input[i])
// 	{
// 		if (ft_isspace(input[i]))
// 			i++;

// 		else if (input[i] == '\'' || input[i] == '"')
// 		{
// 			token = extract_quoted(input, &i);
// 			if (!token && g_shell.last_exit_status == 2)
//             {
//                 return (NULL); // Signal unclosed quote error
//             }
// 			if (token)
// 			{
// 				node = ft_lstnew(token);
// 				gc_add(node, &gc);
// 				ft_lstadd_back(&tokens, node);
// 			}
// 		}
// 		else if (is_special(input + i)) // |, <, >, <<, >>
// 		{
// 			// printf("dkhelt special\n");
// 			token = extract_special(input, &i);
// 			if (!token)
// 				return (NULL);

// 			node = ft_lstnew(token);
// 			gc_add(node, &gc);
// 			ft_lstadd_back(&tokens, node);

// 			if (token->type == TOKEN_HEREDOC)
// 			{
// 				// printf("dkhelt herdoc\n");
// 				t_list *hd_node = extract_heredoc_delimiter(input, &i);
// 				if (hd_node)
// 					ft_lstadd_back(&tokens, hd_node);
// 				continue ; // ✅ skip reprocessing input[i]
// 			}
// 		}
// 		else
// 		{
// 			token = extract_word(input, &i);
// 			if (token)
// 			{
// 				node = ft_lstnew(token);
// 				gc_add(node, &gc);          // << HERE!
// 				ft_lstadd_back(&tokens, node);
// 			}
// 		}
// 	}
// 	return (tokens);
// }
