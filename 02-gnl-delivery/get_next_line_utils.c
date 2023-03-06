/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 04:12:07 by antoda-s          #+#    #+#             */
/*   Updated: 2023/03/06 14:29:53 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/// @brief 		Free allocated memory of a string and inicialize pointer to NULL
/// @param str	Pointer to string
void	ft_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

/// @brief 		Search for a character in a string
/// @param s	String to search
/// @param c	Character to search
/// @return		Pointer to the first occurence of the character in the string
char	*ft_strchr(const char *s, int c)
{
	char	*str;

	if (!s || !*s)
		return (NULL);
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

/// @brief		Count the length of a string
/// @param s	String to count
/// @return		Length of the string
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/// @brief 		Join two strings and frees allocated memory of the first string
/// @param s1	String 1
/// @param s2	String 2
/// @return		Pointer to the new string
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
	if (!dst)
		return (NULL);
	ret = dst;
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

/// @brief 			Allocates and returns a “fresh” substring from the string
///					given as argument. The substring begins at index start and
///					is of size len. If start and len aren’t valid index of "str"
///					the behavior is undefined, Invalid Read Error might happen
///					If the allocating "fresh" fails, the function returns NULL.
/// @param str		String to be cut
/// @param start	Starting index of the substring
/// @param len		Length of the substring
/// @return			Pointer to the substring
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
		while (i < len && str[start + i] != '\0')
		{
			sub[i] = str[start + i];
			i++;
		}
		sub[i] = '\0';
		return (sub);
	}
	return (NULL);
}
