/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:41:10 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/23 13:12:54 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	size_t				i;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
		{
			return (str1[i] - str2[i]);
		}
		i++;
	}
	return (0);
}
/*
#include <stdio.h>

int	main()
{
	char	str1[] = "abcdefg";
	char	str2[] = "abcdefg";
	char	str3[] = "abcdfg";
	int	len;

	len = ft_strlen(str1);
	printf("Strings '%s' - '%s' es '%d'\n", str1, str2, 
	ft_memcmp(str1, str2, len));
	printf("Strings '%s' - '%s' es '%d'\n", str1, str3, 
	ft_memcmp(str1, str3, len));
	return (0);
}
*/
