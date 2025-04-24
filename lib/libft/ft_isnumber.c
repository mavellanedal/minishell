/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:44:52 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/24 16:51:18 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumber(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

/*
#include <stdio.h>
int main(void)
{
    const char *input = "-12345";

    if (ft_isnumber(input))
        printf("La cadena '%s' es un número válido.\n", input);
    else
        printf("La cadena '%s' no es un número válido.\n", input);

    return 0;
}
*/