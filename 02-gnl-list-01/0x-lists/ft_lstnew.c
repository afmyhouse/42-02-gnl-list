/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:41:34 by antoda-s          #+#    #+#             */
/*   Updated: 2023/02/25 14:43:51 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

/// @brief 			Allocates (with malloc(3)) and returns a new element. The
/// The variable ’content’ is initialized with the value of the parameter 
/// ’content’. The variable ’next’ is initialized to NULL.
/// @param content 	The content to create the new element with.
/// @return 		The new element.
t_list	*ft_lstnew(void *content)
{
	t_list	*lstnew;

	lstnew = (t_list *)malloc(sizeof(t_list));
	if (!lstnew)
		return (NULL);
	else
	{
		(*lstnew).content = content;
		(*lstnew).next = NULL;
	}
	return (lstnew);
}
