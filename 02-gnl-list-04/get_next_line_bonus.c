/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 04:12:07 by antoda-s          #+#    #+#             */
/*   Updated: 2023/03/02 17:49:26 by antoda-s         ###   ########.fr       */
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
	if (!(ptr = (t_fd_lst *)malloc(sizeof(t_fd_lst))))
		return (NULL);
	*ptr = (t_fd_lst){fd, NULL, 1, *list};
	*list = ptr;
	return (ptr);
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

	if (line)
	{
		i = 0;
		len = ft_strlen(line);
		tmp = line;
		while (tmp[i])
		{
			if (tmp[i] == '\n')
			{
				node->str = ft_strsub(line, i + 1, len - i);
				line = ft_strsub(line, 0, i + 1);
				if (*node->str  == '\0')
				{
					free(node->str );
					node->str  = NULL;
				}
				free(tmp);
				return (line);
			}
			i++;
		}
	}
	node->str = NULL;
	node->ret = 0;
	if (*line == '\0')
	{
		free(line);
		line = NULL;
	}
	return (line);
}

char	*pending_line(t_fd_lst *node, char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	if (node->str == NULL || *node->str == '\0')
		return (0);
	tmp = node->str;
	while (tmp[i])
	{
		if (tmp[i] == '\n')
		{
			line = ft_strsub(node->str, 0, i + 1);//******
			node->str = ft_strsub(node->str, i + 1, ft_strlen(node->str));
			if (*node->str == '\0')
			{
				free(node->str);
				node->str = NULL;
			}
			free(tmp);
			return (line);
		}
		i++;
	}
	line = node->str;
	node->str = NULL;
	return (line);
}

char		*get_next_line(int fd)
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
	line = pending_line(node, line);
	if (node->str == NULL || *node->str == '\0')
	{
		line = new_line(node, line);
		if(line)
			line = split_read(node, line);
	}

	if ((node->ret == 0 || node->ret == -1) && node->str == NULL )
	{
		fd_lst = node->next;
		free(node);
	}
	/*if (*node->str == '\0' && node)
	{
		free(node->str);
		node->str = NULL;
	}*/
	return (line);
}
/**/
int	main(void)
{
	int		fd, fd1, fd2, fd3;
	char	*line1, *line2, *line3;
	int 	i1 = 0;

	fd1 = open("./files/multiple_nlx5", O_RDONLY);
	fd2 = open("./files/multiple_line_with_nl", O_RDONLY);
	fd3 = open("./files/alternate_line_nl_no_nl", O_RDONLY);

	fd = 1;
	while (fd)
	{
		line1 = get_next_line(fd1);
		if (line1)
		{
			printf("--------- fd = %d - linha %d ----------\n", fd1, ++i);
			printf("%s", line1);
			printf("\n");
			free(line1);
		}
		line2 = get_next_line(fd2);
		if (line2)
		{
			printf("--------- fd = %d - linha %d ----------\n", fd2, ++i);
			printf("%s", line2);
			printf("\n");
			free(line2);
		}
		line3 = get_next_line(fd3);
		if (line3)
		{
			printf("--------- fd = %d - linha %d ----------\n", fd3, ++i);
			printf("%s", line3);
			printf("\n");
			free(line3);
		}
	}
	{
		line1 = get_next_line(fd1);
		if (line1)
		{
			printf("--------- fd = %d - linha %d ----------\n", fd1, ++i1);
			printf("%s", line1);
			printf("\n");
			free(line1);
		}
		line2 = get_next_line(fd2);
		if (line2)
		{
			printf("--------- fd = %d - linha %d ----------\n", fd2, ++i2);
			printf("%s", line2);
			printf("\n");
			free(line2);
		}

	}
	close(fd1);
	close(fd2);
	return (0);
}
/**/
