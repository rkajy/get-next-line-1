/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:28:20 by radandri          #+#    #+#             */
/*   Updated: 2025/09/02 14:52:36 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>  // for open
# include <stdio.h>  // for FILE, remove for PUSH
# include <stdlib.h> // for malloc, free
// # include <sys/types.h> //
// # include <sys/uio.h> // for read, write
# include <unistd.h> // for read, write, close

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

int					read_and_stash(int fd, t_list **stash_ptr);
void				add_to_stash(t_list **stash, char *buf);
char				*extract_line(t_list *stash);
char				*generate_line(t_list *stash);

// Function prototypes for utility functions
int					found_newline(t_list *stash);
char				*ft_strdup(const char *s1);
t_list				*ft_lst_get_last(t_list *stash);
void				free_stash(t_list *stash);
t_list				*clean_stash(t_list *stash);

// Prototype of the redefined function
char				*get_next_line(int fd);

#endif