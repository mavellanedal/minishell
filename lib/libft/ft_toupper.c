/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:31:45 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/18 17:33:46 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

/*
#include <stdio.h>

int main(void)
{
    char c;

    printf("Ingresa un carácter: ");
    scanf("%c", &c);

    char upper = ft_toupper(c);

    printf("El carácter en mayúscula es: %c\n", upper);

    return 0;
}
*/
