/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:27:17 by antoda-s          #+#    #+#             */
/*   Updated: 2023/02/25 14:43:51 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

/// @brief 		Returns the last element of the list.
/// @param lst 	The beginning of the list.
/// @return		The last element of the list.
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if ((*lst).next == NULL)
			return (lst);
		lst = (*lst).next;
	}
	return (lst);
}
