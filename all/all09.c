/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all09.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 04:12:07 by antoda-s          #+#    #+#             */
/*   Updated: 2023/03/05 19:37:42 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all09.h"

void	ft_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	if (!s || !*s)
		return (NULL);
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
	if (!dst)
		return (NULL);
	ret = dst;
	if (s1)
	{
		while (*s1)
			*dst++ = *s1++;
		free((void *)(s1 - (dst - ret)));
	}
	while (*s2)
		*dst++ = *s2++;
	*dst = '\0';
	//ft_strlen(ret);
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

		while (i < len && str[start + i] != '\0')
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
	printf("BREAK NEXT LINE 01\n");
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

char	*get_next_line(int fd)
{
	static t_fd_lst	*fd_lst;
	t_fd_lst		*node;
	char 			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = check_fd(fd, &fd_lst);
		printf("BREAK GET NEXT LINE 01\n");
	if (node == NULL)
		return (NULL);
	printf("BREAK GET NEXT LINE 02\n");
	next_line(node);
	printf("BREAK GET NEXT LINE 03\n");
	line = node->nl;
	if ((node->ret == 0 || node->ret == -1) && (!node->nl || !*node->nl))
	{
		printf("BREAK GET NEXT LINE 04\n");
		fd_lst = node->next;
		printf("BREAK GET NEXT LINE 05\n");
		//if (node)
			free(node);
		printf("BREAK GET NEXT LINE 06\n");
	}
		printf("BREAK GET NEXT LINE 07\n");
	//if (node)
		return (line);
	//else
	//	return (NULL);
}
