/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:28:57 by ebalana-          #+#    #+#             */
/*   Updated: 2024/10/08 12:29:03 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_string(char *str)
{
	int	size;

	size = 0;
	if (str == 0)
	{
		return (ft_print_string("(null)"));
	}
	while (str[size])
	{
		size += ft_print_character(str[size]);
	}
	return (size);
}

int	ft_print_number(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		size += ft_print_character('0');
	if (n == -2147483648)
	{
		size += ft_print_string("-2147483648");
		return (size);
	}
	if (n < 0)
	{
		size += ft_print_character('-');
		n = -n;
	}
	if (n > 0)
		size += ft_print_unsigned((unsigned int)n);
	return (size);
}

int	ft_print_unsigned(unsigned int n)
{
	int	size;

	size = 0;
	if (n == 0)
		size += ft_print_character('0');
	else
	{
		if (n >= 10)
			size += ft_print_unsigned(n / 10);
		size += ft_print_character((n % 10) + '0');
	}
	return (size);
}

int	ft_print_hexadecimal(unsigned long long n, char format)
{
	int		size;
	char	*hex_digits;

	size = 0;
	if (format == 'x')
		hex_digits = "0123456789abcdef";
	else
		hex_digits = "0123456789ABCDEF";
	if (n == 0)
		return (ft_print_character('0'));
	if (n >= 16)
		size += ft_print_hexadecimal(n / 16, format);
	size += ft_print_character(hex_digits[n % 16]);
	return (size);
}

int	ft_print_pointer(unsigned long long ptr)
{
	int	size;

	size = 0;
	if (ptr == 0)
		size += ft_print_string("(nil)");
	else
	{
		size += ft_print_string("0x");
		size += ft_print_hexadecimal(ptr, 'x');
	}
	return (size);
}
