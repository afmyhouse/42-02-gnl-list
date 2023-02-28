/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:44:00 by antoda-s          #+#    #+#             */
/*   Updated: 2023/02/25 14:43:51 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

/// @brief 		Iterates the list ’lst’ and applies the function ’f’ on the 
///				content of each node. Creates a new list resulting of the 
///				successive applications of the function ’f’. The ’del’ function 
///				is used to delete the content of a node if needed.
/// @param lst 	The address of a pointer to a node.
/// @param f 	The address of the function used to iterate on the list.
/// @param del 	The address of the function used to delete the content of a
///				node if needed.
/// @return 	The new list. NULL if the allocation fails.
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lsthead;
	t_list	*lstnew;

	if (!lst)
		return (NULL);
	lstnew = ft_lstnew(f((*lst).buf_read));
	if (!lstnew)
		return (NULL);
	lsthead = lstnew;
	while (lst)
	{
		if ((*lst).next)
		{
			(*lstnew).next = ft_lstnew(f((*(*lst).next).buf_read));
			if (!(*lstnew).next)
			{
				ft_lstdelone(lstnew, del);
				return (NULL);
			}
			lstnew = (*lstnew).next;
		}
		lst = (*lst).next;
	}
	(*lstnew).next = NULL;
	return (lsthead);
}
