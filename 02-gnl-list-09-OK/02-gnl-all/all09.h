/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all09.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 00:52:19 by antoda-s          #+#    #+#             */
/*   Updated: 2023/03/06 15:32:45 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL09_H
# define ALL09_H
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

void		ft_free(char **str);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *s);
char		*ft_strjoin_free(char const *s1, char const *s2);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
t_fd_lst	*check_fd(int fd, t_fd_lst **list);
int			new_line(t_fd_lst *node);
int			next_line(t_fd_lst *node);
char		*get_next_line(int fd);

#endif
