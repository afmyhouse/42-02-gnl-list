/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 04:12:07 by antoda-s          #+#    #+#             */
/*   Updated: 2023/03/06 13:55:31 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/// @brief 		Checks if the fd is already in the list
/// @param fd	Current File Descriptor
/// @param list	Pointer to the head of the list
/// @return		Pointer to the node, new or existing
t_fd_lst	*check_fd(int fd, t_fd_lst **list)
{
	t_fd_lst	*ptr;
	t_fd_lst	*tmp;

	ptr = *list;
	tmp = *list;
	while (ptr != NULL)
	{
		if ((ptr->fd) == fd)
		{
			if (ptr != tmp)
			{
				tmp->next = ptr->next;
				ptr->next = *list;
				*list = ptr;
			}
			return (ptr->nl = NULL, ptr);
		}
		tmp = ptr;
		ptr = ptr->next;
	}
	ptr = (t_fd_lst *)malloc(sizeof(t_fd_lst));
	if (!ptr)
		return (NULL);
	*ptr = (t_fd_lst){fd, NULL, NULL, 1, *list};
	return (*list = ptr, ptr);
}

/// @brief 		Reads the file in slashes of BUFFER_SIZE until it finds a \n
///				or the EOF. It saves the reading at the pointer node->raw.
///				It frees the memory allocated to the reading buffer.
/// @param node	The node with "fd" file descriptor, pointer "raw" to hold
///				reading result and status of reading "ret"
/// @return		1 if it finds a new line, 0 if it reaches the end of the file
int	new_line(t_fd_lst *node)
{
	char	*buff;

	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	buff[0] = '\0';
	while (node->ret != 0 && !ft_strchr(buff, '\n'))
	{
		node->ret = read(node->fd, buff, BUFFER_SIZE);
		if (node->ret < 0)
		{
			ft_free(&buff);
			node->ret = 0;
			return (0);
		}
		buff[node->ret] = '\0';
		if (node->ret)
			node->raw = ft_strjoin_free(node->raw, buff);
	}
	ft_free(&buff);
	return (1);
}

/// @brief 		Checks if there is a complete line (\n) in the raw string.
///				If no \n is not found it calls for a "new line" from file
///				If a complete line is found it copies it to the node->nl
/// @param node	Pointer to the node with fd, pointers "raw" and "nl" and "ret"
/// @return		1 if it finds a new line, 0 if it reaches the end of the file
int	next_line(t_fd_lst *node)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!ft_strchr(node->raw, '\n') && node->ret)
		new_line(node);
	if (node->raw && *node->raw)
	{
		tmp = node->raw;
		while (node->raw[i] && node->raw[i] != '\n')
			i++;
		if (node->raw[i] == '\n')
		{
			i++;
			node->nl = ft_strsub(node->raw, 0, i);
			node->raw = ft_strsub(node->raw, i, ft_strlen(node->raw) - i);
			if (!*node->raw)
				ft_free(&node->raw);
			free(tmp);
			return (1);
		}
		node->nl = node->raw;
	}
	node->raw = NULL;
	return (node->ret = 0, 0);
}

/// @brief 		Allocs & returns a string ending w/ a \n, read from a file fd
///				Each fd should be managed independently of the others
///				- when reading from stdin, the function will keep on reading
///				from the current position even after have read the \n
/// @param fd	File Descriptor
/// @return		The string read from the file descriptor
char	*get_next_line(int fd)
{
	static t_fd_lst	*list;
	t_fd_lst		*node;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = check_fd(fd, &list);
	if (node == NULL)
		return (NULL);
	next_line(node);
	line = node->nl;
	if ((node->ret == 0 || node->ret == -1) && (!node->nl || !*node->nl))
	{
		list = node->next;
		free(node);
	}
	return (line);
}
