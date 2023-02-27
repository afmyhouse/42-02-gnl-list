/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 04:12:07 by antoda-s          #+#    #+#             */
/*   Updated: 2023/02/27 04:17:46 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

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

char	*ft_strdup(const char *s)
{
	char	*dst;
	int		i;

	i = 0;
	if (!(dst = (char *)malloc(sizeof(char) * (ft_strlen((char *)s) + 1))))
		return (NULL);
	while (*s)
		dst[i++] = *s++;
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	int			len;
	char		*dst;
	char		*tmp;
	int			i;

	i = 0;
	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (!(len = ft_strlen((char *)s1) + ft_strlen((char *)s2)))
		return (NULL);
	if ((dst = (char *)malloc(sizeof(char) * (len + 1))))
	{
		tmp = (char *)s1;
		while (*s1)
			dst[i++] = *s1++;
		while (*s2)
			dst[i++] = *s2++;
		dst[i] = '\0';
		free((void *)tmp);
		return (dst);
	}
	return (NULL);
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*cpy;
	unsigned long	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	if ((cpy = (char *)malloc(sizeof(char) * (len + 1))))//len-star+1
	{
		while (i < len)
		{
			cpy[i] = s[start + i];
			i++;
		}
		cpy[i] = '\0';
		return (cpy);
	}
	return (NULL);
}
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	ft_add_fd_node(t_list **list, t_list *new)
{
	new->next = *list;
	*list = new;
}

t_list		*ft_create_fd_node(void const *content, size_t content_size)
{
	t_list *new_fd;

	if (!(new_fd = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
		return (NULL);
	new_fd->content = (void *)content;
	new_fd->content_size = content_size;
	new_fd->next = NULL;
	return (new_fd);
}

t_gnl	*check_fd(int fd, t_list **list)
{
	t_gnl	*gnl_buf;
	t_list		*new;

	new = *list;
	while (new != NULL)
	{
		if (((t_gnl *)new->content)->fd == fd)
			return ((t_gnl *)new->content);
		new = new->next;
	}
	if (!(gnl_buf = malloc(sizeof(t_gnl))))
		return (NULL);
	gnl_buf->str = NULL;
	gnl_buf->fd = fd;
	if ((new = ft_create_fd_node((void *)gnl_buf, 0)) == NULL)
		return (NULL);
	ft_add_fd_node(list, new);
	return (gnl_buf);
}

void	gnl_split_read(char **line, t_gnl *gnl_buf)
{
	int		i;
	int		len;
	char	*tmp;

	if (*line == NULL)
		return ;
	i = 0;
	len = ft_strlen(*line);
	tmp = *line;
	while (tmp[i])
	{
		if (tmp[i] == '\n')
		{
			gnl_buf->str = ft_strsub(*line, i + 1, len + 1);
			*line = ft_strsub(*line, 0, i + 1);
			free(tmp);
			return ;
		}
		i++;
	}
}

int		gnl_new_read(int fd, char **line)
{
	int		ret;
	char	buff[BUFF_SIZE + 1];

	while ((ret = read(fd, buff, BUFF_SIZE)) != 0)
	{
		if (ret == -1)
			return (-1);
		buff[ret] = '\0';
		*line = ft_strjoin_free(*line, buff);
		if (ft_strchr(buff, '\n') != NULL)
			break ;
	}
	if (*line == NULL)
		return (0);
	return (1);
}

int		gnl_pending_read(char **str, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	if (*str == NULL || **str == '\0')
		return (1);
	tmp = *str;
	while (tmp[i])
	{
		if (tmp[i] == '\n')
		{
			*line = ft_strsub(*str, 0, i);
			*str = ft_strsub(*str, i + 1, ft_strlen(*str));
			free(tmp);
			return (0);
		}
		i++;
	}
	*line = *str;
	*str = NULL;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static t_list	*list;
	t_gnl			*gnl_buf;
	int				ret;

	ret = 1;
	if (line == NULL || fd == -1 || (gnl_buf = check_fd(fd, &list)) == NULL)
		return (-1);
	*line = NULL;
	if (gnl_pending_read(&(gnl_buf->str), line))
		ret = gnl_new_read(fd, line);
	//if (!ret)
	//	free(gnl_buf->str)
	gnl_split_read(line, gnl_buf);
	return (ret);
}

int main(void)
{
	int fd1, fd2;
	int rd1 = 1, rd2 = 1;
	char *line;
	int i1 = 0, i2 = 0;

	fd1 = open("file11.txt", O_RDONLY);
	fd2 = open("file22.txt", O_RDONLY);
	
	while (rd1 || rd2)
	{
		rd1 = get_next_line(fd1, &line);
		if (rd1 > 0)
		{
			printf("--------- fd = %d - linha %d ----------\n", fd1, ++i1);
			printf("%s", line);
			printf("\n");
			free(line);
		}
		rd2 = get_next_line(fd2, &line);
		if (rd2 > 0)
		{
			printf("--------- fd = %d - linha %d ----------\n", fd2, ++i2);
			printf("%s", line);
			printf("\n");
			free(line);
		}
	}
	
	close(fd1);
	close(fd2);
	return (0);
}