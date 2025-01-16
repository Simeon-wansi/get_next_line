/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 22:10:30 by sngantch          #+#    #+#             */
/*   Updated: 2025/01/13 19:56:35 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str)
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	if ((char)c == '\0')
		return (str);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sjoint;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	sjoint = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!sjoint)
		return (NULL);
	ft_memcpy(sjoint, s1, s1_len);
	ft_memcpy(sjoint + s1_len, s2, s2_len);
	sjoint[s1_len + s2_len] = '\0';
	return (sjoint);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	s1_len;

	if (!s1)
		return (ft_strdup(""));
	s1_len = ft_strlen(s1);
	str = malloc(s1_len + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, s1_len + 1);
	return (str);
}
