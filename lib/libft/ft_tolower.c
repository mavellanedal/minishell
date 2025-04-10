/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:37:28 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/18 17:38:09 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

/*
#include <stdio.h>

int main(void)
{
    char c;

    printf("Ingresa un carácter: ");
    scanf("%c", &c);

    char lower = ft_tolower(c);

    printf("El carácter en minúscula es: %c\n", lower);

    return 0;
}
*/
