/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 00:52:19 by antoda-s          #+#    #+#             */
/*   Updated: 2023/03/06 15:52:09 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000000
# endif

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_fd_lst
{
	int				fd;
	char			*raw;
	char			*nl;
	int				ret;
	struct s_fd_lst	*next;
}				t_fd_lst;

/* get_next_line_utils_bonus.c */
void		ft_free(char **str);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *s);
char		*ft_strjoin_free(char const *s1, char const *s2);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
/* get_next_line_bonus.c */
t_fd_lst	*check_fd(int fd, t_fd_lst **list);
int			new_line(t_fd_lst *node);
int			next_line(t_fd_lst *node);
char		*get_next_line(int fd);

#endif
