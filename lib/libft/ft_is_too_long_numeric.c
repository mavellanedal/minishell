/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_too_long_numeric.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:44:17 by ebalana-          #+#    #+#             */
/*   Updated: 2025/05/14 17:28:33 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

int	ft_is_too_long_numeric(const char *str)
{
	const char	*limit;
	int			sign;
	int			len;

	limit = "9223372036854775807";
	sign = 1;
	len = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str == '0')
		str++;
	while (str[len] >= '0' && str[len] <= '9')
		len++;
	if (len != 19)
		return (len > 19);
	if (sign == -1)
		limit = "9223372036854775808";
	return (strcmp(str, limit) > 0);
}

/*
int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Uso: %s <numero>\n", argv[0]);
		return (1);
	}

	if (is_too_long_numeric(argv[1]))
		printf("\"%s\" es DEMASIADO largo ❌\n", argv[1]);
	else
		printf("\"%s\" es un número válido en tamaño ✅\n", argv[1]);

	return (0);
}
*/