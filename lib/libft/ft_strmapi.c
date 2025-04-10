/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:19:49 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/26 15:44:45 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*api;

	api = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!api)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		api[i] = (*f)(i, s[i]);
		i++;
	}
	api[i] = '\0';
	return (api);
}
/*
char	rules(unsigned int i, char c)
{
	if (i % 2 == 0)
		return (ft_toupper(c));
	else
		return (ft_tolower(c));
}

#include <stdio.h>

int main(void)
{
	char str[] = "Hola Mundo!";
	char *result;
	
	result = ft_strmapi(str, rules);
	if (result)
	{
		printf("Original: %s\n", str);
		printf("Transformada: %s\n", result);
		free(result);
	}
	else
	{
		printf("Error: No se pudo asignar memoria.\n");
	}
	return (0);
}
*/
