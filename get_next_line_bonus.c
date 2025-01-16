/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 21:38:03 by sngantch          #+#    #+#             */
/*   Updated: 2025/01/15 19:29:15 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	free(*remainder);
	*remainder = temp;
	return (1);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	size_t		bytes_read;
	static char	*fd_buffer[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!fd_buffer[fd] || (!ft_strchr(fd_buffer[fd], '\n')
			&& bytes_read > 0))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == (unsigned long)-1)
			return (free(buffer), free(fd_buffer[fd]), fd_buffer[fd] = NULL,
				NULL);
		buffer[bytes_read] = '\0';
		if (!set_remainder(&fd_buffer[fd], &buffer))
			return (free(buffer), free(fd_buffer[fd]), NULL);
	}
	free(buffer);
	if (!fd_buffer[fd] || *fd_buffer[fd] == '\0')
		return (free(fd_buffer[fd]), fd_buffer[fd] = NULL, NULL);
	return (extract_line(&fd_buffer[fd]));
}
