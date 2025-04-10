/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:10:46 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/19 17:34:28 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	count;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (size <= dst_len)
		return (src_len + size);
	count = dst_len;
	while (*src != '\0' && count < (size - 1))
		*(dst + count++) = *src++;
	*(dst + count) = '\0';
	return (dst_len + src_len);
}

/*
#include <stdio.h>

int main(void) 
{
    char dest[20] = "Hola";  // Cadena destino con espacio
    char src[] = " Mundo!";  // Cadena origen
    size_t size = sizeof(dest);  // Tamaño del buffer destino

    // Llamar a ft_strlcat y guardar el valor retornado
    size_t result = ft_strlcat(dest, src, size);

    // Imprimir los resultados
    printf("Cadena concatenada: %s\n", dest);
    printf("Longitud total que intentó concatenar: %zu\n", result);

    return 0;
}
*/
