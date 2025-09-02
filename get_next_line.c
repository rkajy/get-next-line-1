/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:28:15 by radandri          #+#    #+#             */
/*   Updated: 2025/09/02 14:10:22 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> // REMOVE FOR PUSH

// Adds a new node with the content of buf to the end of the linked list (stash).
void add_to_stash(t_list **stash, char *buf)
{
    int i;
    t_list *last;
    t_list *new_node;

    new_node = malloc(sizeof(t_list));
    if(new_node == NULL)
        return;
    new_node->content = ft_strdup(buf);
    new_node->next = NULL;
    if(new_node->content == NULL)
    {
        free(new_node);
        return;
    }
    i = 0;
    while(buf[i])
    {
        new_node->content[i] = buf[i];
        i++;
    }
    new_node->content[i] = '\0';
    if(*stash == NULL)
        *stash = new_node;
    else
    {
        last = ft_lst_get_last(*stash);
        last->next = new_node;
    }
}

// Uses read() to read from the file descriptor and store the read data into a linked list (stash).
// Continues reading until a newline character is found or the end of the file is reached.
/* Uses read() to add characters to the stash */
int read_and_stash(int fd, t_list **stash_ptr)
{
    char *buf;
    int bytes_read;

    buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (buf == NULL)
        return (-1);

    bytes_read = 1;
    while (!found_newline(*stash_ptr) && bytes_read > 0)
    {
        bytes_read = (int)read(fd, buf, BUFFER_SIZE);
        if(*stash_ptr == NULL && bytes_read <=  0)
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

char* generate_line(t_list *stash)
{
    int i;
    int len;
    t_list *current;

    len = 0;
    current = stash;
    while(current)
    {
        i =0;
        while (current->content[i])
        {
            len++;
            if(current->content[i] == '\n')
                break;
            i++;
        }
        if (current->content[i] == '\n')
            break;
        current =current->next;
    }
    return (malloc(sizeof(char) * (len+1)));
}


// Extracts a line from the linked list (stash) and stores it in the provided line pointer.
char* extract_line(t_list *stash)
{
    int i;
    int j;
    char *line;

    if(stash == NULL)
        return (NULL);
    line = generate_line(stash);
    if(line == NULL)
        return (NULL);
    j = 0;
    while(stash)
    {
        i = 0;
        while(stash->content[i])
        {
            if(stash->content[i] == '\n')
            {
                line[j++] = stash->content[i];
                break;
            }
            line[j++] = stash->content[i++];
        }
        stash = stash->next;
    }
    line[j] = '\0';
    return (line);
}

t_list *ft_lst_get_last(t_list *stash)
{
    t_list *current;

    current = stash;
    while (current && current->next)
        current = current->next;
    return (current);
}



void    free_stash(t_list *stash)
{
    t_list *current;
    t_list *next;

    current = stash;
    while(current)
    {
        free(current->content);
        next = current->next;
        free(current);
        current = next;
    }
}

int found_newline(t_list *stash)
{
    int i;
    t_list *current;

    if(stash == NULL)
        return 0;
    current = ft_lst_get_last(stash);
    i = 0;
    while(current->content[i])
    {
        if(current->content[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

t_list *clean_stash(t_list *stash)
{
    t_list *new_stash = NULL;
    t_list *temp;
    int pos;
    char *leftover;
    if (stash == NULL)
        return (NULL);
    temp = ft_lst_get_last(stash);
    pos = 0;
    while (temp->content[pos] && temp->content[pos] != '\n')
        pos++;
    if (temp->content[pos] == '\n' && temp->content[pos + 1] != '\0')
    {
        leftover = ft_strdup(temp->content + pos + 1);
        if (leftover == NULL)
            return (NULL);
        new_stash = malloc(sizeof(t_list));
        if (new_stash == NULL)
        {
            return (free(leftover), NULL);
        }
        new_stash->content = leftover;
        new_stash->next = NULL;
    }
    free_stash(stash);
    return (new_stash);
}

char *get_next_line(int fd)
{
    // Repeated call using a loop to read from the file descriptor one line at a time.
    // Should return the line was read. If there is nothing to read or an error occurs, it should return NULL.
    // Should works as expected when reading a file and when reading from standard input (stdin).
    // The returned line sould include the terminating \n character, expect when the end and file is reached and the file doesn't end with an newline character.
    static t_list *stash = NULL;
    char    *line;
    int readed;

    if(fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
        return (NULL);
    readed = 1;
    line = NULL;
    // 1. read from fd and add to linked list
    readed = read_and_stash(fd, &stash);
    if (readed == -1)
        return (NULL);
    if (stash == NULL)
        return (NULL);
    // 2. extract from stash to line
    line = extract_line(stash);
    // 3. clean up stash
    stash = clean_stash(stash);
    if(line[0] == '\0')
    {
        free_stash(stash);
        stash = NULL;
        free(line);
        return (NULL);
    }
    return (line);
}

