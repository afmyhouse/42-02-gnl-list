/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all091_main .c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 04:12:07 by antoda-s          #+#    #+#             */
/*   Updated: 2023/03/05 19:29:20 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all09.h"

#  define FILE_3 "./files/multiple_line_with_nl"


int	main(void)
{
	int		fd;
	char	*line;

	int 	i = 1;

	//fd1 = open("./files/multiple_nlx5", O_RDONLY);
	fd = open(FILE_3, O_RDONLY);

	printf("BUFFER_SIZE = %i\n", BUFFER_SIZE);
	printf("file 3 : %s\n", FILE_3);
	printf("\n____________________line at a time____________________\n");
	printf("\n____________________line %i____________________\n",i);

	fd = 1;

	printf("\n____________________file at a time____________________\n");

	fd = open(FILE_3, O_RDONLY);
	printf("\n#_______________ fd%d _______________#\n", fd);
	line = get_next_line(fd);
	i = 1;
	while(line)
	{
		printf("i = %i ;", i);
		printf("%s", line);
		//printf("AFTER Printf line\n");

		free(line);
		//printf("AFTER FREE line\n");

		line = get_next_line(fd);
		//printf("AFTER GET NEXT LINE\n");

		++i;
		//if (i == 6)
		//	printf("BREAKPOINT\n");

	}
	close(fd);

	return (0);
}
