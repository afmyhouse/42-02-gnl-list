get next line version 09
UP to DATE!!!!
Valid version

get_next_line_utils.c | get_next_line_utils_bonus.c
includes 5 functions to handle string arrays

void		ft_free(char **str);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *s);
char		*ft_strjoin_free(char const *s1, char const *s2);
char		*ft_strsub(char const *s, unsigned int start, size_t len);

get_next_line.c | get_next_line_bonus.c
includes 4 functions to handle fd, line and raw readings of the file
t_fd_lst	*check_fd(int fd, t_fd_lst **list);
int			new_line(t_fd_lst *node);
int			next_line(t_fd_lst *node);
char		*get_next_line(int fd);

there is no functional difference between mandatory and bonus files
version delivered at 42
