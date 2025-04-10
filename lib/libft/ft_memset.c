/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:48:18 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/19 12:25:40 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>

int main(void)
{
    char buffer[50] = "Buenos dias!";
   
    printf("Antes de ft_memset: %s\n", buffer);

    ft_memset(buffer, 'X', 5);

    printf("Después de ft_memset: %s\n", buffer);

    return 0;
}
*/
