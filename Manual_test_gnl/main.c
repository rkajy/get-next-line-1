/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:24:21 by radandri          #+#    #+#             */
/*   Updated: 2025/09/01 16:29:13 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <fcntl.h> // For open
#include <stdio.h> // For printf, perror
#include "get_next_line_test.h" // For file macro

int	main(void)
{
    int		fd;
    char	*line;

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (1);
    }

    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}