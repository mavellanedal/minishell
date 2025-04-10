/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:38:09 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/19 12:49:13 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

/*
#include <stdio.h>

int main(void)
{
    char buffer[50] = "Hola Mundo!";
    printf("Antes de ft_bzero: %s\n", buffer);
    ft_bzero(buffer, 5);
    printf("Después de ft_bzero: %s\n", buffer);
    return 0;
}
*/
