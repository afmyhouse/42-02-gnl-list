/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:02:39 by antoda-s          #+#    #+#             */
/*   Updated: 2023/03/01 12:09:20 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_fd_lst	*check_fd(int fd, t_fd_lst **list)
{
	t_fd_lst	*ptr;
	t_fd_lst	*tmp;

	ptr = *list;
	tmp = NULL;
	while (ptr && ptr->fd != fd)
	{
		tmp = ptr;
		ptr = ptr->next;
	}
	ptr = malloc(sizeof(t_fd_lst));
	if (!ptr)
		return (NULL);
	if (tmp)
	{
		tmp->next = ptr->next;
		ptr->next = *list;
	}
	*list = ptr;
	return (ptr->str = NULL, ptr->fd = fd, ptr);
}
