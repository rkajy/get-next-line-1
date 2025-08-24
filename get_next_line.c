/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:28:15 by radandri          #+#    #+#             */
/*   Updated: 2025/08/23 20:02:06 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
    // Repeated call using a loop to read from the file descriptor one line at a time.
    // Should return the line was read. If there is nothing to read or an error occurs, it should return NULL.
    // Should works as expected when reading a file and when reading from standard input (stdin).
    // The returned line sould include the terminating \n character, expect when the end and file is reached and the file doesn't end with an newline character.
}