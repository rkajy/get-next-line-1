/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:28:15 by radandri          #+#    #+#             */
/*   Updated: 2025/09/03 14:06:46 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief Adds a new node containing the given buffer content to the end of
 * the stash list.
 *
 * This function creates a new node, duplicates the content of the provided
 * buffer, and appends the new node to the end of the linked list pointed to
 * by `stash`. If the buffer is NULL or memory allocation fails, the function
 * safely exits.
 *
 * @param stash A double pointer to the head of the linked list (stash).
 * If the list is empty, the new node becomes the head.
 * @param buf A string buffer to be added to the stash. If NULL,
 * the function does nothing.
 *
 * @note The function uses `ft_strdup` to duplicate the buffer content and
 * assumes that `ft_strdup` is implemented elsewhere in the codebase.
 * @note The caller is responsible for ensuring proper memory management of
 * the stash list.
 */
void	add_to_stash(t_list **stash, char *buf)
{
	t_list	*last;
	t_list	*new_node;

	if (buf == NULL)
		return ;
	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->content = ft_strdup(buf);
	if (new_node->content == NULL)
		return (free(new_node));
	new_node->next = NULL;
	if (*stash == NULL)
		*stash = new_node;
	else
	{
		last = *stash;
		while (last && last->next)
			last = last->next;
		last->next = new_node;
	}
}

/**
 * @brief Reads from the file descriptor and adds the data to the stash.
 *
 * This function reads data from the given file descriptor and appends it to
 * the stash linked list. It stops reading when a newline is found or when
 * there is no more data to read.
 *
 * @param fd The file descriptor to read from.
 * @param stash_ptr A double pointer to the stash linked list.
 *
 * @return The number of bytes read, or -1 in case of an error.
 */
int	read_and_stash(int fd, t_list **stash_ptr)
{
	char	*buf;
	int		bytes_read;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (-1);
	bytes_read = 1;
	while (!found_newline(*stash_ptr) && bytes_read > 0)
	{
		bytes_read = (int)read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buf[bytes_read] = '\0';
		add_to_stash(stash_ptr, buf);
	}
	free(buf);
	if (bytes_read < 0)
		return (-1);
	return (bytes_read);
}

/**
 * @brief Allocates memory for a line from the stash.
 *
 * This function calculates the length of the line to be extracted from the
 * stash and allocates memory for it.
 *
 * @param stash A pointer to the stash linked list.
 *
 * @return A pointer to the allocated line, or NULL in case of an error.
 */
char	*generate_line(t_list *stash)
{
	int		i;
	int		len;
	t_list	*current;
	char	*line;

	len = 0;
	current = stash;
	while (current)
	{
		i = 0;
		while (current->content[i])
		{
			len++;
			if (current->content[i] == '\n')
				break ;
			i++;
		}
		if (current->content[i] == '\n')
			break ;
		current = current->next;
	}
	line = malloc(sizeof(char) * (len + 1));
	if (line == NULL)
		return (NULL);
	return (line);
}

/**
 * @brief Extracts a line from the stash.
 *
 * This function extracts a line from the stash linked list, stopping at the
 * first newline character or the end of the stash.
 *
 * @param stash A pointer to the stash linked list.
 *
 * @return A pointer to the extracted line, or NULL in case of an error.
 */
char	*extract_line(t_list *stash)
{
	int		i;
	int		j;
	char	*line;
	int		stop;

	line = generate_line(stash);
	if (line == NULL)
		return (NULL);
	j = 0;
	stop = 0;
	while (stash && !stop)
	{
		i = 0;
		while (stash->content && stash->content[i] && !stop)
		{
			line[j++] = stash->content[i];
			if (stash->content[i] == '\n')
				stop = 1;
			i++;
		}
		stash = stash->next;
	}
	line[j] = '\0';
	return (line);
}

/**
 * @brief Reads the next line from a file descriptor.
 *
 * This function reads the next line from the given file descriptor, using a
 * static stash to store intermediate data between calls.
 *
 * @param fd The file descriptor to read from.
 *
 * @return A pointer to the next line, or NULL if there are no more lines or
 * in case of an error.
 */
char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*line;
	int				status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	status = read_and_stash(fd, &stash);
	if (status == -1)
		return (free_stash(stash), stash = NULL, NULL);
	if (stash == NULL)
		return (NULL);
	line = extract_line(stash);
	stash = clean_stash(stash);
	if (!line || line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}
