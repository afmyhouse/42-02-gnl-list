/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 04:12:07 by antoda-s          #+#    #+#             */
/*   Updated: 2023/03/04 19:42:56 by antoda-s         ###   ########.fr       */
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
			return (ptr);
		}
		tmp = ptr;
		ptr = ptr->next;
	}
	ptr = (t_fd_lst *)malloc(sizeof(t_fd_lst));
	if (!ptr)
		return (NULL);
	*ptr = (t_fd_lst){fd, NULL, 1, *list};
	return (*list = ptr, ptr);
}

char	*new_line(t_fd_lst *node, char *line)
{
	char	*buff;

	buff = (char *)malloc(BUFFER_SIZE + 1);
	buff[0] = '\0';
	while (node->ret != 0 && !ft_strchr(buff, '\n'))
	{
		node->ret = read(node->fd, buff, BUFFER_SIZE);
		if (node->ret == -1)
		{
			free(buff);
			return (0);
		}
		buff[node->ret] = '\0';
		line = ft_strjoin_free(line, buff);
	}
	free(buff);
	return (line);
}

char	*split_read(t_fd_lst *node, char *line)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = ft_strlen(line);
	tmp = line;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (tmp[i] == '\n')
	{
		node->str = ft_strsub(line, i + 1, len - i);
		line = ft_strsub(line, 0, i + 1);
		if (*node->str == '\0')
			ft_free(&node->str);
		free(tmp);
		return (line);
	}
	node->str = NULL;
	node->ret = 0;
	if (*line == '\0')
		ft_free(&line);
	return (line);
}

char	*pending_line(t_fd_lst *node, char *line)
{
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(node->str);
	tmp = node->str;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (tmp[i] == '\n')
	{
		line = ft_strsub(node->str, 0, i + 1);
		node->str = ft_strsub(node->str, i + 1, len - (i + 1));
		if (*node->str == '\0')
			ft_free(&node->str);
		free(tmp);
		return (line);
	}
	line = node->str;
	node->str = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static t_fd_lst	*fd_lst;
	t_fd_lst		*node;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = check_fd(fd, &fd_lst);
	if (node == NULL)
		return (NULL);
	line = NULL;
	if (node->str != NULL && *node->str != '\0')
		line = pending_line(node, line);
	if (node->str == NULL || *node->str == '\0')
	{
		line = new_line(node, line);
		if (line)
			line = split_read(node, line);
	}
	if ((node->ret == 0 || node->ret == -1) && node->str == NULL )
	{
		fd_lst = node->next;
		free(node);
	}
	return (line);
}
