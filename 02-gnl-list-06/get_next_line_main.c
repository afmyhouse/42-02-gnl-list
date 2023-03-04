/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 04:12:07 by antoda-s          #+#    #+#             */
/*   Updated: 2023/03/03 22:16:01 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/get_next_line_bonus.h"

int	main(void)
{
	//int		fd, fd1, fd2;
	int		fd, fd1, fd2, fd3;
	//char	*line1, *line2;
	char	*line1, *line2, *line3;
	int 	i = 0;

	fd1 = open("./files/multiple_nlx5", O_RDONLY);
	fd2 = open("./files/multiple_line_with_nl", O_RDONLY);
	fd3 = open("./files/alternate_line_nl_no_nl", O_RDONLY);

	fd = 1;
	while (fd)
	{
		line1 = get_next_line(fd1);
		if (line1)
		{
			printf("--------- fd = %d - linha %d ----------\n", fd1, ++i);
			printf("%s", line1);
			printf("\n");
			free(line1);
		}
		line2 = get_next_line(fd2);
		if (line2)
		{
			printf("--------- fd = %d - linha %d ----------\n", fd2, ++i);
			printf("%s", line2);
			printf("\n");
			free(line2);
		}
		line3 = get_next_line(fd3);
		if (line3)
		{
			printf("--------- fd = %d - linha %d ----------\n", fd3, ++i);
			printf("%s", line3);
			printf("\n");
			free(line3);
		}
		if (!line1 && !line2 && !line3)
			fd = 0;
	}

	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
