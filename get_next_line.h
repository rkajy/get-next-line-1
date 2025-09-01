/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:28:20 by radandri          #+#    #+#             */
/*   Updated: 2025/09/01 22:43:43 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>  // for open
# include <stdio.h>  // for FILE, remove for PUSH
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

int found_newline(t_list *stash);
t_list *ft_lst_get_last(t_list *stash);
int read_and_stash(int fd, t_list **stash_ptr);
void add_to_stash(t_list **stash, char *buf);
char* extract_line(t_list *stash);
char* generate_line(t_list *stash);
//void clean_stash(t_list **stash);
int ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void free_stash(t_list *stash);


// Function prototypes for utility functions
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memmove(void *dst, const void *src, size_t len);

// Prototype of the redefined function
char	*get_next_line(int fd);

#endif