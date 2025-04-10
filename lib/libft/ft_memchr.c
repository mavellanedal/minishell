/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:26:55 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/23 12:22:57 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	unsigned char		count;
	size_t				i;

	ptr = (const unsigned char *)s;
	count = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == count)
		{
			return ((void *)&ptr[i]);
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main()
{
	char	s[] = "Hola Mundo!";
	char	c = 'e';
	int	len;
	char	*result;

	len = ft_strlen(s);
	result = ft_memchr(s, c, len);
	if (result != NULL)
	{
		printf("String despues de '%c' es '%s\n'", c, result);
	}
	else
	{
		printf("Caracter '%c' no encontrado en string '%s' \n", c, s);
	}
	return (0);
}
*/
