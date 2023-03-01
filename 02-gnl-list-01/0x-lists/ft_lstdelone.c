/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:43:10 by antoda-s          #+#    #+#             */
/*   Updated: 2023/02/25 14:43:51 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

/// @brief 		Deletes the element given as the parameter.
/// @param lst 	The element to be deleted.
/// @param del 	The address of the function used to delete the content of the element.
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del((*lst).content);
	free(lst);
}
