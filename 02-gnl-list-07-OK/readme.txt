get next line version 07
OUTDATED!!!!
replaced by otimization v09

#FILE 1
get_next_line_utils.c | get_next_line_utils_bonus.c

includes 5 functions to handle string arrays

void		ft_free(char **str);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *s);
char		*ft_strjoin_free(char const *s1, char const *s2);
char		*ft_strsub(char const *s, unsigned int start, size_t len);

#FILE 2
get_next_line.c | get_next_line_bonus.c

includes 5 functions to handle fd, line and raw readings of the file

t_fd_lst	*check_fd(int fd, t_fd_lst **list);
char		*split_read(t_fd_lst *fd_node, char *line);
char		*new_line(t_fd_lst *node, char *line);
char		*pending_line(t_fd_lst *fd_node, char *line);
char		*get_next_line(int fd);

there is no functional difference between mandatory and bonus files
version not delivered at 42
