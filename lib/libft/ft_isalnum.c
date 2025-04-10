/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:27:22 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/18 16:27:46 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
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

    if (ft_isalnum(c))
        printf("'%c' es un carácter alfanumérico.\n", c);
    else
        printf("'%c' NO es un carácter alfanumérico.\n", c);

    return 0;
}
*/
