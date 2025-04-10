/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:23:13 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/20 16:32:54 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	len;

	len = ft_strlen(s);
	i = len;
	while (i >= 0)
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i--;
	}
	return (NULL);
}

/*
#include <stdio.h>

int	main()
{
	const char *s = "Hola Mundo!";
	int	c = '!';
	char	*result;
	int	pos_rev;

	printf("Se buscara la posicion del caracter '%c' en la frase %s\n", c, s);

	result = ft_strrchr(s,c);
	pos_rev = ft_strlen(s) - (result - s);
	if (result != NULL)
	{
		printf("Caracter '%c' se ha encontrado en 
		la posicion '%d'\n", c, pos_rev);
	}
	else
	{
		printf("Caracter '%c' no se ha encontrado.\n", c);
	}
	return (0);
}
*/
