/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:20:53 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/18 16:21:45 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
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

    if (ft_isalpha(c))
        printf("'%c' es una letra.\n", c);
    else
        printf("'%c' no es una letra.\n", c);

    return 0;
}
*/
