/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:47:05 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/25 13:03:07 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!join)
		return (NULL);
	ft_memcpy(join, s1, s1_len);
	ft_memcpy(join + s1_len, s2, s2_len);
	join[s1_len + s2_len] = '\0';
	return (join);
}
/*
#include <stdio.h>

int	main()
{
	char	s1[] = "Hola";
	char	s2[] = " 42";
	char	*merge;
	
	printf("String 1: %s\n", s1);
	printf("String 2: %s\n", s2);
	merge = ft_strjoin(s1, s2);
	printf("Juntas: %s\n", merge);
	free(merge);
	return (0);
}
*/
