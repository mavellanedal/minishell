/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_numeric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:28:04 by ebalana-          #+#    #+#             */
/*   Updated: 2025/05/14 14:30:44 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

int	ft_is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Uso: %s <string>\n", argv[0]);
		return (1);
	}

	if (ft_is_numeric(argv[1]))
		printf("\"%s\" es un número válido ✅\n", argv[1]);
	else
		printf("\"%s\" NO es un número válido ❌\n", argv[1]);

	return (0);
}
*/