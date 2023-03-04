/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_all.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 04:12:07 by antoda-s          #+#    #+#             */
/*   Updated: 2023/03/04 00:22:45 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	if (*str == c)
		return (str);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	int		len;
	char	*dst;
	char	*ret;

	if (!s1 || !*s1)
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	ret = dst;
	if (!dst)
		return (NULL);
	if (s1)
	{
		while (*s1)
			*dst++ = *s1++;
		free((void *)(s1 - (dst - ret)));
	}
	while (*s2)
		*dst++ = *s2++;
	*dst = '\0';
	return (ret);
}

char	*ft_strsub(char const *str, unsigned int start, size_t len)
{
	char			*sub;
	unsigned long	i;

	if (!str)
		return (NULL);
	i = 0;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (sub)
	{
		while (i < len)
		{
			sub[i] = str[start + i];
			i++;
		}
		sub[i] = '\0';
		return (sub);
	}
	return (NULL);
}

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

	i = 0;
	len = ft_strlen(line);
	tmp = line;
	while (tmp && tmp[i] && tmp[i]!= '\n')
		i++;
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
	node->str = NULL;
	node->ret = 0;
	if (*line == '\0')
		free(line);
	return (line = NULL);
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
	if (!line || !ft_strchr(line, '\n'))
		line = new_line(node, line);
	if(line)
		line = split_read(node, line);

	if ((node->ret == 0 || node->ret == -1) && node->str == NULL )
	{
		fd_lst = node->next;
		free(node);
	}
	return (line);
}

int	main(void)
{
	//int		fd, fd1, fd2;
	int		fd, fd1, fd2, fd3;
	//char	*line1, *line2;
	char	*line1, *line2, *line3;
	int 	i = 0;

	fd1 = open("../files/multiple_nlx5", O_RDONLY);
	fd2 = open("../files/multiple_line_with_nl", O_RDONLY);
	fd3 = open("../files/alternate_line_nl_no_nl", O_RDONLY);

	fd = 1;
	while (fd)
	{
		line1 = get_next_line(fd1);
		if (line1)
		{
			printf("--------- fd = %d - linha %d ----------\n", fd1, i);
			printf("%s", line1);
			printf("X\n");
			free(line1);
		}
		line2 = get_next_line(fd2);
		if (line2)
		{
			printf("--------- fd = %d - linha %d ----------\n", fd2, i);
			printf("%s", line2);
			printf("X\n");
			free(line2);
		}
		line3 = get_next_line(fd3);
		if (line3)
		{
			printf("--------- fd = %d - linha %d ----------\n", fd3, i);
			printf("%s", line3);
			printf("X\n");
			free(line3);
		}
		if (!line1 && !line2 && !line3)
			fd = 0;
		++i;
	}

	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
