/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:46:58 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/20 15:56:34 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if ((unsigned char)c == '\0')
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main()
{
	const char *s = "Hola Mundo!";
	int	c = 'n';
	char	*result;

	printf("Se buscara la posicion del caracter '%c' en la frase %s\n", c, s);

	result = ft_strchr(s,c);
	if (result != NULL)
	{
		printf("Caracter '%c' se ha encontrado en la 
		posicion '%ld'\n", c, result - s);
	}
	else
	{
		printf("Caracter '%c' no se ha encontrado.\n", c);
	}
	return (0);
}
*/
