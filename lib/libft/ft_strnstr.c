/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:15:38 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/23 13:58:11 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (i < len && big[i] != '\0')
	{
		j = 0;
		while (i + j < len && big[i + j] == little[j] && little[j] != '\0')
		{
			j++;
		}
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main()
{
	const char big[] = "Hola Mundo!";
	const char little[] = "Mun";
	const char not_found[] = "adios";
	size_t len = 9;

	char *result = ft_strnstr(big, little, len);
	if (result)
		printf("Subcadena '%s' encontrada en '%s': '%s'\n", little, big, result);
	else
		printf("Subcadena '%s' no encontrada en '%s' en los primeros 
		%zu caracteres\n", little, big, len);

	result = ft_strnstr(big, not_found, len);
    	if (result)
		printf("Subcadena '%s' encontrada en '%s': '%s'\n", 
		not_found, big, result);
	else
		printf("Subcadena '%s' no encontrada en '%s' en los primeros 
		%zu caracteres\n", not_found, big, len);

	return 0;
}
*/
