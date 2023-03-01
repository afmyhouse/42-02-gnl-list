t_fd_lst	*check_fd(int fd, t_fd_lst **list)
{
	t_fd_lst	*ptr;
	t_fd_lst	*tmp;
	ptr = *list;
	tmp = *list;
	while (ptr != NULL)
	{
		if ((ptr->fd) == fd && ptr != tmp)
		{
				tmp->next = ptr->next;
				ptr->next = *list;
				*list = ptr;
				return (ptr);
		}
		else if((ptr->fd) == fd && ptr == tmp)
			return (ptr);
		tmp = ptr;
		ptr = ptr->next;
	}
	if (!(ptr = (t_fd_lst *)malloc(sizeof(t_fd_lst))))
		return (NULL);
	ptr->str = NULL;
	ptr->fd = fd;
	ptr->next = *list;
	*list = ptr;
	return (ptr);
}
