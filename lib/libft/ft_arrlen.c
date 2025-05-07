/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:02:56 by ebalana-          #+#    #+#             */
/*   Updated: 2025/05/06 18:04:14 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

/*
int main(void)
{
	char *test1[] = {"uno", "dos", "tres", NULL};
	char *test2[] = {NULL};
	char *test3[] = {"solo", NULL};

	printf("Test 1: %d (esperado: 3)\n", ft_arrlen(test1));
	printf("Test 2: %d (esperado: 0)\n", ft_arrlen(test2));
	printf("Test 3: %d (esperado: 1)\n", ft_arrlen(test3));

	return (0);
}
*/