/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:28:20 by radandri          #+#    #+#             */
/*   Updated: 2025/08/30 21:49:47 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>  // for open
# include <stdio.h>  // for FILE
# include <stdlib.h> // for malloc, free
# include <unistd.h> // for read, write, close
# include <sys/uio.h>
# include <sys/types.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
# endif

typedef struct s_list
{
    char *content;
    struct s_list *next;
} t_list;


// Function prototypes for utility functions
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memmove(void *dst, const void *src, size_t len);

// Prototype of the redefined function
char	*get_next_line(int fd);

#endif