/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:15:57 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/30 13:44:57 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}
/*
#include <stdio.h>

int	main()
{
	t_list	*size;
	size = ft_lstnew("Hola Mundo");
	
	printf("La frase es %s y tiene %d nodo", 
	(char *)size -> content, ft_lstsize(size));
	free(size);
	return (0);
}
*/
