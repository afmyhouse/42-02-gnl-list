# get_next_line

The third project at school 42 requires you to build a function that reads a file up to the next newline character, building a string of its text up to this point, and assigning this string to a pointer given as a parameter. For the full brief see the get_next_line.en.pdf.

The function is dependent on usage of functions created in our first project ‘libft’, which is included in this repository. 

My version utilises a static linked list. When a new-line character is found in the sring built by read, its index is found, and the string before this index is assigned to *line, while the leftover is assigned to a struct that contains a char pointer (*leftover) and an int fd. Each time a different fd is piped in, a new struct is created, and a node with a pointer to it is added to the linked list. During successive calls to get_next_line, the list is checked to see if there is already any 'leftover' string for that fd, before calling read again.

Prototype: 

int	get_next_line(int fd, char **line)

Return value:

Get next line returns (1) if there is still more of the file to read, (0) if the whole file has been read, and (-1) if there are any errors.
