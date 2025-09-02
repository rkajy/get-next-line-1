/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:28:15 by radandri          #+#    #+#             */
/*   Updated: 2025/09/02 17:29:49 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*line;
	int				status;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
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
