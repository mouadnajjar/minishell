/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/05/02 16:51:12 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/parser.h"

void *gc_malloc(t_list *gc, size_t size)
{
    void *ptr;
	t_list *node;


	ptr = malloc(size);
    if (!ptr)
        return NULL;

    node = ft_lstnew(ptr);
    if (!node)
    {
        free(ptr);
        return NULL;
    }
    ft_lstadd_back(&gc->content, node);
    return ptr;
}

void gc_free_all(t_list *gc)
{
    ft_lstclear(&gc->content, free);
}
