/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:39:16 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/20 16:52:09 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}
/*
#include <stdio.h>

int	main() 
{
    	char str1[] = "Hola";
    	char str2[] = "";
   	char str3[] = "Hdios";
   	
    	printf("Comparando '%s' y '%s': %d\n",str1,str2,ft_strncmp(str1,str2,5));
    	printf("Comparando '%s' y '%s': %d\n",str2,str3,ft_strncmp(str2,str3,5));
	printf("Comparando '%s' y '%s': %d\n",str1,str3,ft_strncmp(str1,str3,5));

	return 0;
}
*/
