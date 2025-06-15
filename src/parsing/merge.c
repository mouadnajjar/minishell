/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/14 20:29:44 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

void	merge_tokens(t_list *curr, t_token *a, t_token *b)
{
	size_t	len;
	char	*merged;
	t_list	*to_remove;

	len = ft_strlen(a->value) + ft_strlen(b->value) + 1;
	merged = gc_alloc(len, &gc);
	ft_strlcpy(merged, a->value, len);
	ft_strlcat(merged, b->value, len);
	a->value = merged;
	a->can_expand &= b->can_expand;
	a->end_index = b->end_index;
	to_remove = curr->next;
	curr->next = to_remove->next;
}

int	has_no_space_between(t_token *a, t_token *b, const char *input)
{
	int	i;

	i = a->end_index + 1;
	while (i < b->start_index)
	{
		if (ft_isspace(input[i]))
			return (0);
		i++;
	}
	return (1);
}

void	merge_adjacent_words(t_list **tokens, const char *input)
{
	t_list	*curr;
	t_token	*a;
	t_token	*b;

	curr = *tokens;
	while (curr && curr->next)
	{
		a = curr->content;
		b = curr->next->content;
		if (a->type == TOKEN_WORD && b->type == TOKEN_WORD)
		{
			if (has_no_space_between(a, b, input))
			{
				merge_tokens(curr, a, b);
				continue ;
			}
		}
		curr = curr->next;
	}
}

// void merge_adjacent_words(t_list **tokens, const char *input)
// {
// 	t_list *curr = *tokens;

// 	while (curr && curr->next)
// 	{
// 		t_token *a = curr->content;
// 		t_token *b = curr->next->content;
// 		// Only merge if both are words
// 		if (a->type == TOKEN_WORD && b->type == TOKEN_WORD)
// 		{
// 			// Look between end of a and start of b in original input
// 			int mid_start = a->end_index + 1;
// 			int mid_end = b->start_index;

// 			int has_space = 0;
// 			int i = mid_start;
// 			while (i < mid_end)
// 			{
// 				if (ft_isspace(input[i]))
// 				{
// 					has_space = 1;
// 					break ;
// 				}
// 				i++;
// 			}
// 			if (!has_space)
// 			{
// 				char *merged = gc_alloc(ft_strlen(a->value)
						// + ft_strlen(b->value) + 1, &gc);
// 				ft_strlcpy(merged, a->value, ft_strlen(a->value)
					// + ft_strlen(b->value) + 1);
// 				ft_strlcat(merged, b->value, ft_strlen(a->value)
					// + ft_strlen(b->value) + 1);
// 				//printf("[merge] '%s' + '%s' => '%s'\n", a->value, b->value,
					// merged); // 🟢 Debug line
// 				a->value = merged;
// 				a->can_expand &= b->can_expand;
// 				a->end_index = b->end_index;

// 					t_list *to_remove = curr->next;
// 				curr->next = to_remove->next;
// 				//free(to_remove);
// 				continue ;
// 			}
// 		}
// 		curr = curr->next;
// 	}
// }
