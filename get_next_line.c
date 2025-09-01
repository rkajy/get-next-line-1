/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:28:15 by radandri          #+#    #+#             */
/*   Updated: 2025/09/01 17:44:48 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> // REMOVE FOR PUSH

// Adds a new node with the content of buf to the end of the linked list (stash).
void add_to_stash(t_list **stash, char *buf, int readed)
{
    int i;
    t_list *last;
    t_list *new_node;

    new_node = malloc(sizeof(t_list));
    if(new_node == NULL)
        return;
    new_node->next = NULL;
    new_node->content = malloc(sizeof(char) * (readed + 1));
    if(new_node->content == NULL)
    {
        free(new_node);
        return;
    }
    i = 0;
    while(buf[i] && i < readed)
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
void read_and_stash(int fd, t_list **stash, int *readed_ptr)
{
    char *buf;

    while(!found_newline(*stash) && *readed_ptr != 0)
    {
        buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
        if(buf == NULL)
            return;
        *readed_ptr = (int)read(fd, buf, BUFFER_SIZE);
        if((*stash == NULL && *readed_ptr ==  0) || *readed_ptr == -1)
        {
            free(buf);
            return;
        }
        buf[*readed_ptr] = '\0';
        add_to_stash(stash, buf, *readed_ptr);
        free(buf);
    }
}

void generate_line(char **line, t_list *stash)
{
    int i;
    int len;

    len = 0;
    while(stash)
    {
        i =0;
        while (stash->content[i])
        {
            if(stash->content[i] == '\n')
            {
                len++;
                break;
            }
            len++;
            i++;
        }
        stash =stash->next;
    }
    *line = malloc(sizeof(char) * (len+1));
}


// Extracts a line from the linked list (stash) and stores it in the provided line pointer.
void extract_line(t_list *stash, char **line_ptr)
{
    int i;
    int j;

    if(stash == NULL)
        return;
    generate_line(line_ptr, stash);
    if(*line_ptr == NULL)
        return;
    j = 0;
    while(stash)
    {
        i = 0;
        while(stash->content[i])
        {
            if(stash->content[i] == '\n')
            {
                (*line_ptr)[j++] = stash->content[i];
                break;
            }
            (*line_ptr)[j++] = stash->content[i++];
        }
        stash = stash->next;
    }
    (*line_ptr)[j] = '\0';
}

t_list *ft_lst_get_last(t_list *stash)
{
    t_list *current;

    current = stash;
    while (current && current->next)
        current = current->next;
    return (current);
}

int ft_strlen(const char *str)
{
    int len;

    len = 0;
    while (*(str++))
        len++;
    return (len);
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

void clean_stash(t_list **stash)
{
    t_list *last;
    t_list *clean_node;
    int i;
    int j;

    clean_node = malloc(sizeof(t_list));
    if(stash == NULL || clean_node == NULL)
        return;
    clean_node->next = NULL;
    last = ft_lst_get_last(*stash);
    i = 0;
    while (last->content[i] && last->content[i] != '\n')
        i++;
    if(last->content && last->content[i] == '\n')
        i++;
    clean_node->content = malloc(sizeof(char) * ((ft_strlen(last->content) - i)+ 1));
    if(clean_node->content == NULL)
        return;
    j = 0;
    while(last->content[i])
        clean_node->content[j++] = last->content[i++];
    clean_node->content[j] = '\0';
    free_stash(*stash);
    *stash = clean_node;
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
    read_and_stash(fd, &stash, &readed);
    if(stash == NULL)
        return (NULL);
    // 2. extract from stash to line
    extract_line(stash, &line);
    // 3. clean up stash
    clean_stash(&stash);
    if(line[0] == '\0')
    {
        free_stash(stash);
        stash = NULL;
        free(line);
        return (NULL);
    }
    return (line);
}

