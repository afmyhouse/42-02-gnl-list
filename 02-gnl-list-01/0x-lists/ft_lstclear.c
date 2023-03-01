/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:41:59 by antoda-s          #+#    #+#             */
/*   Updated: 2023/02/25 14:43:51 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

/// @brief 		Deletes and frees the given element and every successor of that
///				element, using the function ’del’ and free(3). 
///				Finally, the pointer to the list must be set to NULL.
/// @param lst 	The adress of a pointer to an element.
/// @param del 	The address of the function used to delete the content of the element.
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lstclear;
	t_list	*lstnext;

	if (!lst)
		return ;
	lstclear = *lst;
	while (lstclear)
	{
		lstnext = (*lstclear).next;
		ft_lstdelone(lstclear, del);
		lstclear = lstnext;
	}
	*lst = NULL;
}
