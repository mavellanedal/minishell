/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:24:04 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/18 16:25:37 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
#include <stdio.h>

int main(void)
{
    char c;

    printf("Ingresa un carácter: ");
    scanf("%c", &c);

    if (ft_isdigit(c))
        printf("'%c' es un dígito.\n", c);
    else
        printf("'%c' no es un dígito.\n", c);

    return 0;
}
*/
