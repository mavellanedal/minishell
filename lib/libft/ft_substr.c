/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:00:24 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/25 12:26:43 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	total_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	total_len = s_len - start;
	if (total_len > len)
		total_len = len;
	sub = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!sub)
		return (NULL);
	ft_memcpy(sub, s + start, total_len);
	sub[total_len] = '\0';
	return (sub);
}
/*
#include <stdio.h>

int	main()
{
	char	s[] = "Hola 42!";
	char	*sub;
	
	printf("Cadena: %s\n", s);

	sub = ft_substr(s, 1, 7);
	printf("Subcadena: %s\n", sub);

	free(sub);
	return (0);
}
*/
