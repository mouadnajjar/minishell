/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:28:11 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/11 14:27:15 by ahlahfid         ###   ########.fr       */
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
