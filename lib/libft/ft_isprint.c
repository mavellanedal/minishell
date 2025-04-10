/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:47:16 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/18 16:47:35 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c < 127)
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

    if (ft_isprint(c))
        printf("El valor '%d' es un carácter imprimible.\n", c);
    else
        printf("El valor '%d' no es un carácter imprimible.\n", c);

    return 0;
}
*/
