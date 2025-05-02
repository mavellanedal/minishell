/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:34:01 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/24 16:35:20 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

/*
#include <stdio.h>

int	main()
{
	char str1[] = "Hola";
	char str2[] = "";
	char str3[] = "Hdios";

	printf("Comparando '%s' y '%s': %d\n",str1,str2,ft_strncmp(str1,str2));
	printf("Comparando '%s' y '%s': %d\n",str2,str3,ft_strncmp(str2,str3));
	printf("Comparando '%s' y '%s': %d\n",str1,str3,ft_strncmp(str1,str3));

	return 0;
}
*/