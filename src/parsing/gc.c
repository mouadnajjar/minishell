/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/14 20:29:37 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

void	gc_add(void *ptr, t_list **gc)
{
	t_list	*node;

	if (!ptr)
		return ;
	node = ft_lstnew(ptr);
	if (!node)
		return ;
	ft_lstadd_back(gc, node);
}

char	*gc_substr(const char *s, unsigned int start, size_t len, t_list **gc)
{
	char	*substr;

	substr = ft_substr(s, start, len);
	if (!substr)
		return (NULL);
	gc_add(substr, gc);
	return (substr);
}

void	*gc_alloc(size_t size, t_list **gc)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	gc_add(ptr, gc);
	return (ptr);
}

char	*gc_strdup(const char *s, t_list **gc)
{
	char	*dup;

	dup = ft_strdup(s);
	if (!dup)
		return (NULL);
	gc_add(dup, gc);
	return (dup);
}

void	gc_free_all(t_list **gc)
{
	t_list	*tmp;

	while (*gc)
	{
		tmp = (*gc)->next;
		free((*gc)->content);
		free(*gc);
		*gc = tmp;
	}
}
