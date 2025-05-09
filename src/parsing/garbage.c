/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/05/03 11:30:40 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

void *gc_malloc(t_list **gc, size_t size)
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
    ft_lstadd_back(gc, node);
    return ptr;
}

void gc_free_all(t_list **gc)
{
    ft_lstclear(gc, free);
    *gc = NULL;
}
