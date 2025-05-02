/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:28:11 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/02 15:42:41 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*fnode;

	fnode = malloc(sizeof(t_list));
	if (!fnode)
		return (fnode = NULL);
	fnode->content = content;
	fnode->next = NULL;
	return (fnode);
}
