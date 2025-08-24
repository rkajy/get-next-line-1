/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:29:30 by radandri          #+#    #+#             */
/*   Updated: 2025/08/23 18:27:30 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief Fills the first `len` bytes of the memory area pointed to by `b`
 *        with the constant byte `c`.
 *
 * @param b Pointer to the memory area to be filled.
 * @param c The value to be set. It is passed as an int but is converted to
 *          an unsigned char.
 * @param len The number of bytes to be set to the value.
 * @return A pointer to the memory area `b`.
 */
void	*ft_memset(void *b, int c, size_t len)
{
	char			*array;
	unsigned char	copy;
	int				i;

	array = (char *)(b);
	copy = (unsigned char)c;
	i = 0;
	while (i <= (int)len - 1)
	{
		array[i] = copy;
		i++;
	}
	return (b);
}

/**
 * @brief Copies `len` bytes from memory area `src` to memory area `dst`.
 *        The memory areas may overlap; the copy is performed in a way
 *        that ensures the original data in `src` is copied correctly.
 *
 * @param dst Pointer to the destination memory area.
 * @param src Pointer to the source memory area.
 * @param len Number of bytes to copy.
 * @return A pointer to the destination memory area (`dst`).
 *
 * @note If both `dst` and `src` are NULL, the function returns NULL.
 *       The function handles overlapping memory areas by copying
 *       backwards if `dst` is located after `src`.
 */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*cdest;
	char	*csrc;
	size_t	i;

	cdest = (char *)dst;
	csrc = (char *)src;
	if (!dst && !src)
		return (NULL);
	if (cdest > csrc)
	{
		while (len > 0)
		{
			len--;
			cdest[len] = csrc[len];
		}
		return (dst);
	}
	i = 0;
	while (i < len)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dst);
}
