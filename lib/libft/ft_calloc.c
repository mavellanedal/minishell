/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:52:01 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/23 17:04:41 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = malloc(count * size);
	if (!result)
		return (NULL);
	else
	{
		ft_bzero(result, (count * size));
		return (result);
	}
}
/*
#include <stdio.h>

int	main()
{
	size_t	count = 5;
	size_t 	size = sizeof(int);
	size_t	i;
	int	*result;

	result = (int *)ft_calloc(count, size);
	if (result == NULL)
	{
		printf("Error: no se pudo asignar memoria.\n");
		return (1);
	}

	printf("Valores inicializados con ft_calloc:\n");
	i = 0;
	while (i < count)
	{
		printf("result[%zu] = %d\n", i , result[i]);
		i++;
	}
	free(result);
}
*/
