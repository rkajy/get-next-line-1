/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:28:15 by radandri          #+#    #+#             */
/*   Updated: 2025/09/02 15:11:38 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	add_to_stash(t_list **stash, char *buf)
{
	int		i;
	t_list	*last;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->content = ft_strdup(buf);
	new_node->next = NULL;
	if (new_node->content == NULL)
		return (free(new_node));
	i = 0;
	while (buf[i])
	{
		new_node->content[i] = buf[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*stash == NULL)
		*stash = new_node;
	else
	{
		last = ft_lst_get_last(*stash);
		last->next = new_node;
	}
}

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
		if (*stash_ptr == NULL && bytes_read <= 0)
		{
			free(buf);
			return (-1);
		}
		buf[bytes_read] = '\0';
		add_to_stash(stash_ptr, buf);
	}
	free(buf);
	return (bytes_read);
}

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

char	*extract_line(t_list *stash)
{
	int		i;
	int		j;
	char	*line;

	line = generate_line(stash);
	if (line == NULL)
		return (NULL);
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				line[j++] = stash->content[i];
				break ;
			}
			line[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	line[j] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*line;
	int				readed;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	readed = 1;
	line = NULL;
	readed = read_and_stash(fd, &stash);
	if (readed == -1)
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
