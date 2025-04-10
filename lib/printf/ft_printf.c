/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:41:58 by ebalana-          #+#    #+#             */
/*   Updated: 2025/01/16 14:19:11 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_character(int character)
{
	write(1, &character, 1);
	return (1);
}

int	ft_select_format(va_list arg, const char word)
{
	int	size;

	size = 0;
	if (word == 'c')
		size += ft_print_character(va_arg(arg, int));
	else if (word == 's')
		size += ft_print_string(va_arg(arg, char *));
	else if (word == 'd' || word == 'i')
		size += ft_print_number(va_arg(arg, int));
	else if (word == 'u')
		size += ft_print_unsigned(va_arg(arg, unsigned int));
	else if (word == 'x' || word == 'X')
		size += ft_print_hexadecimal(va_arg(arg, unsigned int), word);
	else if (word == 'p')
		size += ft_print_pointer(va_arg(arg, unsigned long long));
	else
		size += ft_print_character(word);
	return (size);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		size;
	va_list	arg;

	i = 0;
	size = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			size += ft_select_format(arg, str[i + 1]);
			i++;
		}
		else
			size += ft_print_character(str[i]);
		i++;
	}
	va_end(arg);
	return (size);
}
/*
#include <stdio.h>
int	main()
{
	ft_printf("Caracters: \n");
	ft_printf("Probando con el caracter '%c'\n", ' ');
	ft_printf("Probando con el caracter '%c'\n", 'z');
	ft_printf("Probando con el caracter '%c'\n", '\n');
	ft_printf("\n");
	ft_printf("Caracters (printf): \n");
	printf("Probando con el caracter '%c'\n", ' ');
	printf("Probando con el caracter '%c'\n", 'z');
	printf("Probando con el caracter '%c'\n", '\n');


	ft_printf("\n");
	ft_printf("Strings: \n");
	ft_printf("Estamos en %d %s y esta siendo guai \n", 42, "Barcelona");
	ft_printf("Vamos a %s el %s \n", "reventar", "cursus");
	ft_printf("Si se puede %s, porque %s es tan guapeton %c \n", \
	 "jodeeer", "arnau", '?');	 
 	ft_printf("\n");
	ft_printf("Strings (printf): \n");
 	printf("Estamos en %d %s y esta siendo guai \n", 42, "Barcelona");
	printf("Vamos a %s el %s \n", "reventar", "cursus");
	printf("Si se puede %s, porque %s es tan guapeton %c \n", \
	 "jodeeer", "arnau", '?');


	ft_printf("\n");
	ft_printf("Unsigned: \n");
	ft_printf("El número sin signo es: %u\n", 0);
	ft_printf("El número sin signo es: %u\n", 123456789);
	ft_printf("El número sin signo es: %u\n", 4294967295);
	ft_printf("\n");
	ft_printf("Unsigned (printf): \n");
	printf("El número sin signo es: %u\n", 0);
	printf("El número sin signo es: %u\n", 123456789);
	printf("El número sin signo es: %lu\n", 4294967295);


	ft_printf("\n");	
	ft_printf("Hexadecimal: \n");
	ft_printf("El número en hexadecimal (minúsculas) es: %x\n", 255); 
	ft_printf("El número en hexadecimal (mayúsculas) es: %X\n", 255);
	ft_printf("Otro número en hexadecimal (minúsculas) es: %x\n", 3735928559);
	ft_printf("\n");
	ft_printf("Hexadecimal (printf): \n");
	printf("El número en hexadecimal (minúsculas) es: %x\n", 255);
	printf("El número en hexadecimal (mayúsculas) es: %X\n", 255);
	printf("Otro número en hexadecimal (minúsculas) es: %lx\n", 3735928559);


	ft_printf("\n");
	ft_printf("Pointers: \n");
	int num = 743;
	void *ptr = &num;
	ft_printf("La dirección de memoria del puntero es: %p\n", ptr);
	ft_printf("Otro puntero es: %p\n", &ft_printf);
	ft_printf("\n");
	ft_printf("Pointers (printf): \n");
	printf("La dirección de memoria del puntero es: %p\n", ptr);
	printf("Otro puntero es: %p\n", &ft_printf);
	
	void *null_ptr = NULL;
    	ft_printf("Test con NULL: %p\n", null_ptr);
    	printf("Test con NULL (printf): %p\n", null_ptr);

	return (0);
}
*/
