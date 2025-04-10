/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:19:30 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/23 16:40:57 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*d;
	int		i;

	i = 0;
	d = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (d == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}
/*
#include <stdio.h>

int	main()
{
	char	s[] = "Hola Mundo!";
	printf("Duplicado: %s\n",  ft_strdup(s));
	return (0);
}
*/
