/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 04:12:07 by antoda-s          #+#    #+#             */
/*   Updated: 2023/03/06 15:40:53 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	if (*str == c)
		return (str);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	int		len;
	char	*dst;
	char	*ret;

	if (!s1 || !*s1)
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	ret = dst;
	if (!dst)
		return (NULL);
	if (s1)
	{
		while (*s1)
			*dst++ = *s1++;
		free((void *)(s1 - (dst - ret)));
	}
	while (*s2)
		*dst++ = *s2++;
	*dst = '\0';
	return (ret);
}

char	*ft_strsub(char const *str, unsigned int start, size_t len)
{
	char			*sub;
	unsigned long	i;

	if (!str)
		return (NULL);
	i = 0;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (sub)
	{
		while (i < len && str[start + i])
		{
			sub[i] = str[start + i];
			i++;
		}
		sub[i] = '\0';
		return (sub);
	}
	return (NULL);
}
