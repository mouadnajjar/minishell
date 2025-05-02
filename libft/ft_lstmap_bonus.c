/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:59:11 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/02 15:42:37 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*hnode;
	t_list	*head;
	void	*ncontent;

	head = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		ncontent = f(lst->content);
		hnode = ft_lstnew(ncontent);
		if (!hnode)
		{
			if (ncontent)
				del(ncontent);
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, hnode);
		lst = lst->next;
	}
	return (head);
}
