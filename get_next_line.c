/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:59:22 by sngantch          #+#    #+#             */
/*   Updated: 2025/01/15 16:25:44 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (0);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	while (dstsize > 1 && *src)
	{
		*dst++ = *src++;
		dstsize--;
	}
	*dst = '\0';
	return (src_len);
}

char	*extract_line(char **remainder)
{
	char	*line;
	char	*new_line_pos;
	char	*temp;

	new_line_pos = ft_strchr(*remainder, '\n');
	if (!new_line_pos)
	{
		line = ft_strdup(*remainder);
		free(*remainder);
		*remainder = NULL;
	}
	else
	{
		line = ft_substr(*remainder, 0, new_line_pos - *remainder + 1);
		temp = ft_strdup(new_line_pos + 1);
		free(*remainder);
		*remainder = temp;
	}
	return (line);
}

int	set_remainder(char **remainder, char **buffer)
{
	char	*temp;

	if (!(*remainder))
	{
		*remainder = ft_strdup(*buffer);
		if (!(*remainder))
			return (0);
		return (1);
	}
	temp = ft_strjoin((*remainder), (*buffer));
	if (!temp)
		return (0);
	free (*remainder);
	*remainder = temp;
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*buffer;
	size_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!remainder || (!ft_strchr(remainder, '\n') && bytes_read > 0))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == (unsigned long)-1)
			return (free(buffer), free(remainder), remainder = NULL, NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!set_remainder(&remainder, &buffer))
			return (free(buffer), free(remainder), NULL);
	}
	free(buffer);
	if (!remainder || *remainder == '\0')
		return (free(remainder), remainder = NULL, NULL);
	return (extract_line(&remainder));
}
