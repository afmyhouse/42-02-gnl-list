/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 04:12:07 by antoda-s          #+#    #+#             */
/*   Updated: 2023/03/01 13:34:07 by antoda-s         ###   ########.fr       */
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

char	*ft_strsub(char const *str, unsigned int start, size_t len)
{
	char			*sub;
	unsigned long	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	if ((sub = (char *)malloc(sizeof(char) * (len + 1))))//len-star+1
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
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
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
	ptr->next = *list;
	*list = ptr;
	return (ptr->str = NULL, ptr->fd = fd, ptr);
}

int	split_read(char *line, t_fd_lst *fd_node)
{
	int		i;
	int		len;
	char	*tmp;

	if (line == NULL)
		return (0);
	i = 0;
	len = ft_strlen(line);
	tmp = line;
	while (tmp[i])
	{
		if (tmp[i] == '\n')
		{
			fd_node->str = ft_strsub(line, i + 1, len + 1);
			line = ft_strsub(line, 0, i + 1);
			free(tmp);
			return (1);
		}
		i++;
	}
	return (0);
}

char		*new_read(int fd, char *line)
{
	int		ret;
	char	buff[BUFF_SIZE + 1];

	while ((ret = read(fd, buff, BUFF_SIZE)) != 0)
	{
		//if ()
		//	return (0);
		buff[ret] = '\0';
		line = ft_strjoin_free(line, buff);
		if (ft_strchr(buff, '\n') != NULL)
			break ;
	}
	if (line == NULL || ret == 0)
		return (0);
	return (line);
}

char		*pending_line(char *str)
{
	char	*tmp;
	char	*line;
	int		i;

	i = 0;
	if (str == NULL || *str == '\0')
		return (0);
	tmp = str;
	while (tmp[i])
	{
		if (tmp[i] == '\n')
		{
			line = ft_strsub(str, 0, i+1);
			str = ft_strsub(str, i + 1, ft_strlen(str));
			free(tmp);
			return (line);
		}
		i++;
	}
	line = str;
	str = NULL;
	return (line);
}

//int		get_next_line(int fd, char **line)
char	*get_next_line(int fd)//, char **line
{
	static t_fd_lst	*fd_lst;
	t_fd_lst		*fd_node;
	int				ret;
	char			*line;

	ret = 1;
	if (fd < 0 || BUFF_SIZE < 1)
		return (0);
	if ((fd_node = check_fd(fd, &fd_lst)) == NULL)
		return (0);
	line = pending_line(fd_node->str);
	if (!line || ft_strchr(line, '\n') == NULL)
		line = new_read(fd, line);
	split_read(line, fd_node);
	if (ret == 0 || ret == -1)
	{
		free(fd_node->str);//?? not sure "str" exists at this stage
		fd_lst = fd_node->next;
		free(fd_node);
	}
	return (line);
}

int main(void)
{
	int fd1, fd2;
	int rd1 = 1, rd2 = 1;
	char *line;
	int i1 = 0, i2 = 0;

	fd1 = open("file111.txt", O_RDONLY);
	fd2 = open("file222.txt", O_RDONLY);

	while (rd1 || rd2)
	{
		//rd1 = get_next_line(fd1, &line);
		line = get_next_line(fd1);
		if (rd1 > 0)
		{
			printf("--------- fd = %d - linha %d ----------\n", fd1, ++i1);
			printf("%s", line);
			printf("\n");
			if(!line)
				rd1 = 0;			
			//free(line);
		}
		//rd2 = get_next_line(fd2, &line);
		line = get_next_line(fd2);
		if (rd2 > 0)
		{
			printf("--------- fd = %d - linha %d ----------\n", fd2, ++i2);
			printf("%s", line);
			printf("\n");
			if(!line)
				rd2 = 0;	
			//free(line);
		}
	}
	//free(line);
	close(fd1);
	close(fd2);
	return (0);
}
