/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:12:53 by ebalana-          #+#    #+#             */
/*   Updated: 2024/10/07 13:13:19 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_print_character(int character);
int	ft_printf(const char *str, ...);
int	ft_print_string(char *str);
int	ft_print_number(int n);
int	ft_print_unsigned(unsigned int n);
int	ft_print_hexadecimal(unsigned long long n, char format);
int	ft_print_pointer(unsigned long long ptr);

#endif
