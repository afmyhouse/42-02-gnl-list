/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:41:34 by antoda-s          #+#    #+#             */
/*   Updated: 2023/02/25 14:43:51 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

/// @brief 		Adds the node ’new’ at the end of the list.
/// @param lst 	The address of a pointer to the first link of a list.
/// @param new 	The address of a pointer to the node to be added to the list. 
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_back;

	if (*lst)
	{
		lst_back = ft_lstlast(*lst);
		(*lst_back).next = &*new;
	}
	else
		*lst = new;
}
