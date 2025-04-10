/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:28:05 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/26 17:29:51 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
/*
int	main()
{
	char	str[] = "Hola 42";
	ft_putendl_fd(str, 2);
	return (0);
}
*/
