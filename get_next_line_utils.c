/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:29:30 by radandri          #+#    #+#             */
/*   Updated: 2025/09/02 17:46:44 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(t_list *stash)
{
	int		i;
	t_list	*current;

	if (stash == NULL)
		return (0);
	current = stash;
	i = 0;
	while (current)
	{
		i = 0;
		while (current->content && current->content[i])
			if (current->content[i++] == '\n')
				return (1);
		current = current->next;
	}
	return (0);
}

char	*ft_strdup(const char *s1)
{
	size_t	s1_len;
	size_t	i;
	char	*res;

	s1_len = 0;
	while (s1[s1_len] != '\0')
		s1_len++;
	i = 0;
	res = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (!res)
		return (NULL);
	while (i < s1_len)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

t_list	*ft_lst_get_last(t_list *stash)
{
	t_list	*current;

	current = stash;
	while (current && current->next)
		current = current->next;
	return (current);
}

void	free_stash(t_list *stash)
{
	t_list	*current;
	t_list	*next;

	current = stash;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}

t_list	*clean_stash(t_list *stash)
{
	t_list	*new_stash;
	t_list	*cur;
	int		i;
	char	*leftover;

	new_stash = NULL;
	cur = stash;
	while (cur)
	{
		i = -1;
		while (cur->content && cur->content[++i])
		{
			if (cur->content[i] == '\n')
			{
				if (cur->content[i + 1] != '\0')
				{
					leftover = ft_strdup(cur->content + i + 1);
					if (!leftover)
						return (free_stash(stash), NULL);
					new_stash = (t_list *)malloc(sizeof(t_list));
					if (!new_stash)
						return (free(leftover), free_stash(stash), NULL);
					new_stash->content = leftover;
					new_stash->next = NULL;
				}
				return (free_stash(stash), new_stash);
			}
		}
		cur = cur->next;
	}
	return (free_stash(stash), NULL);
}
