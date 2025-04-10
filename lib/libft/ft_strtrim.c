/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:23:02 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/25 14:14:45 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (s1[end - 1] && ft_strchr(set, s1[end - 1]) && end > start)
		end--;
	trim = (char *)malloc(sizeof(char) * (end - start + 1));
	if (trim)
		ft_strlcpy(trim, &s1[start], end - start + 1);
	return (trim);
}
/*
#include <stdio.h>

int	main()
{
	char	s1[] = "Hola 42";
	char	s2[] = "Hola ";
	char	*trim;
	
	printf("Original: %s\n", s1);
	trim = ft_strtrim(s1, s2);
	printf("Recorte: %s\n", trim);
	free(trim);
	return (0);
}
*/
