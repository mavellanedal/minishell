/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:34:13 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/26 17:36:39 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar('-', fd);
		ft_putchar('2', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else if (n < 0)
	{
		ft_putchar('-', fd);
		n = -n;
		ft_putnbr_fd(n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar(n + 48, fd);
}
/*
int main() 
{
    ft_putnbr_fd(42, 2);
    ft_putchar('\n', 1);
    ft_putnbr_fd(-1234, 1);
    ft_putchar('\n', 1);
    ft_putnbr_fd(0, 3);
    ft_putchar('\n', 1);
    ft_putnbr_fd(-2147483648, 2);
    ft_putchar('\n', 1);
    ft_putnbr_fd(2147483647, 1);
    ft_putchar('\n', 1);
    return 0;
}
*/
