/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:24:21 by radandri          #+#    #+#             */
/*   Updated: 2025/09/03 13:40:52 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_test.h" // For file macro
#include <fcntl.h>              // For open
#include <stdio.h>              // For printf, perror

int	main(void)
{
	char	*line;
	int		fd;
	int		i;

	i = 1;
	fd = open(FILE_TEST, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	while (i <= 2)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}
