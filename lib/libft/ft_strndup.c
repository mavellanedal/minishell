/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:58:01 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/22 17:59:48 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
/*
#include <stdio.h>
int	main(void)
{
	const char *str = "Hola, soy un string muy largo que voy a cortar.";
	char *duplicado;

	// Test de ft_strndup: copiar solo los primeros 10 caracteres
	duplicado = ft_strndup(str, 10);
	if (duplicado)
	{
		printf("Original: %s\n", str);
		printf("Duplicado (10 caracteres): %s\n", duplicado);
		free(duplicado); // No olvides liberar la memoria
	}
	else
	{
		printf("Error al duplicar la cadena.\n");
	}

	// Test con un número mayor que la longitud de la cadena
	duplicado = ft_strndup(str, 100); // Copiar más allá de la longitud
	if (duplicado)
	{
		printf("Duplicado (100 caracteres): %s\n", duplicado);
		free(duplicado);
	}
	else
	{
		printf("Error al duplicar la cadena.\n");
	}

	return 0;
}
*/
