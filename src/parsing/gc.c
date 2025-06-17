/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/17 15:18:29 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

void	gc_add(void *ptr)
{
	t_list	*node;

	if (!ptr)
		return ;
	node = ft_lstnew(ptr);
	if (!node)
		return ;
	ft_lstadd_back(&g_shell.gc, node);
}

char	*gc_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;

	substr = ft_substr(s, start, len);
	if (!substr)
		return (NULL);
	gc_add(substr);
	return (substr);
}

void	*gc_alloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	gc_add(ptr);
	return (ptr);
}

char	*gc_strdup(const char *s)
{
	char	*dup;

	dup = ft_strdup(s);
	if (!dup)
		return (NULL);
	gc_add(dup);
	return (dup);
}

void	gc_free_all(void)
{
	t_list	*tmp;

	while (g_shell.gc)
	{
		tmp = (g_shell.gc)->next;
		free((g_shell.gc)->content);
		free(g_shell.gc);
		g_shell.gc = tmp;
	}
}
