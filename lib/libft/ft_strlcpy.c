/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:31:44 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/19 16:31:47 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	i = 0;
	while (src[src_len] != '\0')
	{
		src_len++;
	}
	if (size > 0)
	{
		while (i < (size - 1) && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}

/*
#include <stdio.h>

int	main()
{
	char	src[] = "Hola Mundo!";
	char	dst[20];
	
	printf("Cadena original: %s\n", src);
	
	size_t	length = ft_strlcpy(dst, src, sizeof(dst));
	
	printf("Cadena copiada: %s\n", dst);
	printf("Longitud de src: %zu\n", length);
	
	return (0);
}
*/
