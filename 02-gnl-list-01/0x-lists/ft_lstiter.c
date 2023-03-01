/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:43:34 by antoda-s          #+#    #+#             */
/*   Updated: 2023/02/26 23:54:22 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

/// @brief 		Iterates the list ’lst’ and applies the function ’f’ to the 
///				content of each element.
/// @param lst 	The address of a pointer to an element.
/// @param f 	The address of the function used to iterate on the list.
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f((*lst).str_keep);
		lst = (*lst).next;
	}
}
