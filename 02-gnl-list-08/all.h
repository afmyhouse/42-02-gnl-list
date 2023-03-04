/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 11:59:20 by slynn-ev          #+#    #+#             */
/*   Updated: 2023/03/04 20:03:57 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
//987654321098765432109876543210987654321098
typedef struct s_fd_lst
{
	int				fd;
	char			*str;
	int				ret;
	struct s_fd_lst	*next;
}				t_fd_lst;

void		ft_free(char **str);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
char		*ft_strjoin_free(char const *s1, char const *s2);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
t_fd_lst	*check_fd(int fd, t_fd_lst **list);
char		*split_line(t_fd_lst *fd_node, char *line);
char		*new_line(t_fd_lst *node, char *line);
char		*pending_line(char *str, char *line);
char		*get_next_line(int fd);

#endif
