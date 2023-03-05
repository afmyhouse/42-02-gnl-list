/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all09_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 04:12:07 by antoda-s          #+#    #+#             */
/*   Updated: 2023/03/05 19:14:29 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all09.h"

#  define FILE_3 "./files/multiple_line_with_nl"
#  define FILE_4 "./files/multiple_line_no_nl"
#  define FILE_5 "./files/alternate_line_nl_with_nl"
#  define FILE_6 "./files/alternate_line_nl_no_nl"

int	main(void)
{
	int		fd;
	char	*line;
	int		fd3, fd4, fd5, fd6;
	char	*line3, *line4, *line5, *line6;
	int 	i = 1;

	//fd1 = open("./files/multiple_nlx5", O_RDONLY);
	fd3 = open(FILE_3, O_RDONLY);
	fd4 = open(FILE_4, O_RDONLY);
	fd5 = open(FILE_5, O_RDONLY);
	fd6 = open(FILE_6, O_RDONLY);
	printf("BUFFER_SIZE = %i\n", BUFFER_SIZE);
	printf("file 3 : %s\n", FILE_3);
	printf("\n____________________line at a time____________________\n");
	printf("\n____________________line %i____________________\n",i);

	fd = 1;
	while (fd)
	{
		fd =0;
		if ((line = get_next_line(fd3)))
		{
			fd = 1;
			printf("--------- fd%d :", fd3);
			printf("%s", line);
			free(line);
		}
		if ((line = get_next_line(fd4)))
		{
			fd = 1;
			printf("--------- fd%d :", fd4);
			printf("%s", line);
			free(line);
		}
		if ((line = get_next_line(fd5)))
		{
			fd = 1;
			printf("--------- fd%d :", fd5);
			printf("%s", line);
			free(line);
		}
		if ((line = get_next_line(fd6)))
		{
			fd = 1;
			printf("--------- fd%d :", fd6);
			printf("%s", line);
			free(line);
		}
		++i;
		if (i == 10)
			printf("\n__________________BREAKPOINT____________________\n");
		if (fd)
			printf("\n____________________line %i____________________\n",i);
	}

	close(fd3);
	close(fd4);
	close(fd5);
	close(fd6);
	printf("\n_______________end of a line at a time________________\n");

	printf("\n____________________file at a time____________________\n");

	fd3 = open(FILE_3, O_RDONLY);
	printf("\n#_______________ fd%d _______________#\n", fd3);
	line3 = get_next_line(fd3);
	i = 1;
	while(line3)
	{
		printf("%s", line3);
		free(line3);
		line3 = get_next_line(fd3);
		++i;
	}
	close(fd3);
	fd4 = open(FILE_4, O_RDONLY);
	printf("\n#_______________ fd%d _______________#\n", fd4);
	line4 = get_next_line(fd4);
	i = 1;
	while(line4)
	{
		printf("%s", line4);
		free(line4);
		line4 = get_next_line(fd4);
		++i;
	}
	close(fd4);
	fd5 = open(FILE_5, O_RDONLY);
	printf("\n#_______________ fd%d _______________#\n", fd5);
	line5 = get_next_line(fd5);
	i = 1;
	while(line5)
	{
		printf("%s", line5);
		free(line5);
		line5 = get_next_line(fd5);
		++i;
	}
	close(fd5);
	fd6 = open(FILE_6, O_RDONLY);
	printf("\n#_______________ fd%d _______________#\n", fd6);
	line6 = get_next_line(fd6);
	i = 1;
	while(line6)
	{
		printf("%s", line6);
		free(line6);
		line6 = get_next_line(fd6);
		++i;
	}
	close(fd6);
	printf("\n_______________end of a file at a time________________\n");

	return (0);
}
