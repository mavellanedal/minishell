/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:13:38 by ebalana-          #+#    #+#             */
/*   Updated: 2025/02/19 12:13:57 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit_str(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

/*
#include <stdio.h>

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <string>\n", argv[0]);
		return (1);
	}
	if (ft_isdigit_str(argv[1]))
		printf("The string '%s' contains only digits.\n", argv[1]);
	else
		printf("The string '%s' contains non-digit characters.\n", argv[1]);
	return (0);
}
*/