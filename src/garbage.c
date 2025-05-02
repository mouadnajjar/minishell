/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/05/02 15:38:22 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/parce.h"

void *gc_malloc(t_gc *gc, size_t size)
{
    void *ptr = malloc(size);
    if (!ptr)
        return NULL;

    t_list *node = ft_lstnew(ptr);
    if (!node)
    {
        free(ptr);
        return NULL;
    }
    ft_lstadd_back(&gc->allocs, node);
    return ptr;
}

void gc_free_all(t_gc *gc)
{
    ft_lstclear(&gc->allocs, free);
}
