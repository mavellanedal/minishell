/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:19:51 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/26 15:18:09 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*minnumber(int n)
{
	char	*a;

	if (n == -2147483648)
	{
		a = malloc(12);
		a[0] = '-';
		a[1] = '2';
		a[2] = '1';
		a[3] = '4';
		a[4] = '7';
		a[5] = '4';
		a[6] = '8';
		a[7] = '3';
		a[8] = '6';
		a[9] = '4';
		a[10] = '8';
		a[11] = 0;
	}
	else
	{
		a = malloc(2);
		a[0] = '0';
		a[1] = 0;
	}
	return (a);
}

int	checklen(int n)
{
	int	p;

	p = 0;
	while (n != 0)
	{
		n = n / 10;
		p++;
	}
	return (p);
}

char	*ft_itoa(int n)
{
	int		neg;
	int		len;
	char	*result;

	neg = 0;
	if (n == -2147483648 || n == 0)
		return (minnumber(n));
	else if (n < 0)
		neg = 1;
	if (neg == 1)
		n = n * -1;
	len = checklen(n);
	result = malloc(len + neg + 1);
	if (!result)
		return (0);
	result[len + neg] = 0;
	result[0] = '-';
	while (n > 0)
	{
		result[len - !neg] = (n % 10) + 48;
		n = n / 10;
		len--;
	}
	return (result);
}
/*
#include <stdio.h>

int	main(void)
{
    printf("Numero: %s", ft_itoa(321345234));
    printf("Numero: %s", ft_itoa(34));
    printf("Numero: %s", ft_itoa(0));
    return (0);
}
*/
