/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:29:30 by radandri          #+#    #+#             */
/*   Updated: 2025/09/03 14:08:47 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief Checks if there is a newline character in the stash.
 *
 * This function iterates through the stash linked list and checks if any
 * node contains a newline character (`\n`).
 *
 * @param stash A pointer to the stash linked list.
 *
 * @return 1 if a newline is found, 0 otherwise.
 */
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

/**
 * @brief Duplicates a string.
 *
 * This function allocates memory and creates a duplicate of the given string.
 *
 * @param s1 The string to duplicate.
 *
 * @return A pointer to the duplicated string, or NULL if memory allocation
 * fails.
 */
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

/**
 * @brief Frees the entire stash linked list.
 *
 * This function iterates through the stash linked list and frees all nodes
 * and their associated content.
 *
 * @param stash A pointer to the stash linked list.
 */
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

/**
 * @brief Duplicates the content of the stash after the first newline.
 *
 * This function finds the first newline character in the stash and duplicates
 * the content that comes after it.
 *
 * @param stash A pointer to the stash linked list.
 *
 * @return A pointer to the duplicated content, or NULL if there is no content
 * after the newline.
 */
char	*dup_after_newline(t_list *stash)
{
	t_list	*cur;
	int		i;

	cur = stash;
	while (cur)
	{
		i = 0;
		while (cur->content && cur->content[i])
		{
			if (cur->content[i] == '\n')
			{
				if (cur->content[i + 1] != '\0')
					return (ft_strdup(cur->content + i + 1));
				return (NULL);
			}
			i++;
		}
		cur = cur->next;
	}
	return (NULL);
}

/**
 * @brief Cleans the stash and keeps only the content after the first newline.
 *
 * This function removes all nodes from the stash and creates a new stash
 * containing only the content after the first newline character.
 *
 * @param stash A pointer to the stash linked list.
 *
 * @return A pointer to the new stash, or NULL if there is no content after
 * the newline.
 */
t_list	*clean_stash(t_list *stash)
{
	t_list	*new_stash;
	char	*leftover;

	leftover = dup_after_newline(stash);
	free_stash(stash);
	if (!leftover)
		return (NULL);
	new_stash = malloc(sizeof(t_list));
	if (!new_stash)
	{
		free(leftover);
		return (NULL);
	}
	new_stash->content = leftover;
	new_stash->next = NULL;
	return (new_stash);
}
