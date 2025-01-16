/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:32:43 by sngantch          #+#    #+#             */
/*   Updated: 2025/01/16 14:43:40 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line1;
	char	*line2;

	fd1 = open("fichier.txt", O_RDONLY);
	fd2 = open("fichier2.txt", O_RDONLY);
	if (fd1 == -1 || fd2 == -1)
		return (perror("Error opening file"), 1);
	while (1)
	{
		line1 = get_next_line(fd1);
		if (!line1)
			break ;
		printf("%s", line1);
		free(line1);
	}
	close(fd1);
	while (1)
	{
		line2 = get_next_line(fd2);
		if (!line2)
			break ;
		printf("%s", line2);
		free(line2);
	}
	close(fd2);
}
