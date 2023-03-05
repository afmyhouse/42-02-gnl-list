/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 04:12:07 by antoda-s          #+#    #+#             */
/*   Updated: 2023/03/05 18:54:39 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

int	next_line(t_fd_lst *node)
{
	int		len;
	int		i;
	char	*tmp;
	
	i = 0;
	if (!ft_strchr(node->raw, '\n') && node->ret)
		new_line(node);
	if (node->raw && *node->raw)
	{
		len = ft_strlen(node->raw);
		tmp = node->raw;
		while (node->raw[i] && node->raw[i] != '\n')
			i++;
		if (node->raw[i] == '\n')
		{
			i++;
			node->nl = ft_strsub(node->raw, 0, i);
			node->raw = ft_strsub(node->raw, i, len - i);
			if (!*node->raw)
				ft_free(&node->raw);
			free(tmp);
			return (1);
		}
		node->nl = node->raw;
	}
	node->raw = NULL;
	node->ret = 0;
	return (0);
}
/*
int	next_line(t_fd_lst *node)
{
	int		len;
	int		i;

	i = 0;
	if (!ft_strchr(node->raw, '\n') && node->ret)
		new_line(node);
	if (node->raw && *node->raw)
	{
		len = ft_strlen(node->raw);
		while (node->raw[i] && node->raw[i] != '\n')
			i++;
		if (node->raw[i] == '\n')
		{
			i++;
			node->nl = ft_strsub(node->raw, 0, i);
			node->raw = ft_strsub(node->raw, i, len - i);
			if (!*node->raw)
				ft_free(&node->raw);
			return (1);
		}
		node->nl = node->raw;
	}
	node->raw = NULL;
	node->ret = 0;
	return (0);
}*/

char	*get_next_line(int fd)
{
	static t_fd_lst	*fd_lst;
	t_fd_lst		*node;
	char 			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = check_fd(fd, &fd_lst);
	if (node == NULL)
		return (NULL);
	next_line(node);
	line = node->nl;
	if ((node->ret == 0 || node->ret == -1) && (!node->nl || !*node->nl))
	{
		fd_lst = node->next;
		free(node);
	}
	return (node->nl);
}
