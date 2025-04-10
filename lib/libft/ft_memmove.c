/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:21:10 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/19 16:26:18 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	if (!dest && !src)
		return (NULL);
	if (d < s || d >= s + n)
	{
		while (n--)
		{
			*d++ = *s++;
		}
	}
	else
	{
		d += n;
		s += n;
		while (n--)
		{
			*(--d) = *(--s);
		}
	}
	return (dest);
}

/*
#include <stdio.h>

int main(void)
{
    char buffer[50] = "Hola Mundo!";

    printf("Contenido antes de ft_memmove: %s\n", buffer);

    // Copiar de una posición a otra en el mismo buffer (superposición)
    ft_memmove(buffer + 5, buffer, 12);

    // Imprimir el contenido del buffer después de la llamada a ft_memmove
    printf("Contenido del buffer después de ft_memmove: %s\n", buffer);

    return 0;
}
*/
