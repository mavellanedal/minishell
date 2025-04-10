/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:01:06 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/19 13:08:24 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	size_t				i;

	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

/*
#include <stdio.h>

int main(void) 
{
    char src[] = "Hola Mundo! 42";
    char dest[50] = {0};  // Inicializar el buffer de destino con ceros
    
    printf("Contenido antes de ft_memcpy: %s\n", src);

    // Usar ft_memcpy para copiar 12 bytes de src a dest
    ft_memcpy(dest, src, 12);

    // Imprimir el contenido del buffer de destino
    printf("Contenido de dest: %s\n", dest);  // Debería imprimir "Hola Mundo!"

    return 0;
}
*/
