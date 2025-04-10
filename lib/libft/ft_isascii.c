/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:46:11 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/18 16:46:20 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/*
#include <stdio.h>

int main(void)
{
    int c;

    printf("Ingresa un valor numérico para el carácter: ");
    scanf("%d", &c);

    if (ft_isascii(c))
        printf("El valor '%d' está dentro del rango ASCII.\n", c);
    else
        printf("El valor '%d' no está dentro del rango ASCII.\n", c);

    return 0;
}
*/
