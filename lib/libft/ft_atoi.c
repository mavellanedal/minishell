/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:27:05 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/23 15:47:50 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		||nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
	{
		i++;
	}
	if (nptr[i] == '-')
		sign *= -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * result);
}
/*
#include <stdio.h>

int	main()
{
	char	str1[] = "    --42";
	char    str2[] = "12345abc";
	char    str3[] = "hola42";

	printf("Resultado con '%s': %d\n", str1, ft_atoi(str1));
	printf("Resultado con '%s': %d\n", str2, ft_atoi(str2));
	printf("Resultado con '%s': %d\n", str3, ft_atoi(str3));
	return (0);
}
*/
