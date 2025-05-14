/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_echo_n_flag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:26:20 by ebalana-          #+#    #+#             */
/*   Updated: 2025/05/14 16:28:16 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

int	ft_is_echo_n_flag(const char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

/*
int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Uso: %s <arg1> [arg2] ...\n", argv[0]);
		return (1);
	}

	for (int i = 1; i < argc; i++)
	{
		if (ft_is_echo_n_flag(argv[i]))
			printf("\"%s\" es un flag -n válido ✅\n", argv[i]);
		else
			printf("\"%s\" NO es un flag -n válido ❌\n", argv[i]);
	}

	return (0);
}
*/