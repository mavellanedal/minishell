/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:49:36 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/30 13:06:28 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new || !lst)
		return ;
	new -> next = *lst;
	*lst = new;
}
/*
#include <stdio.h>

void print_list(t_list *lst)
{
	while (lst)
	{
		printf("%s -> ", (char *)lst -> content);
		lst = lst -> next;
	}
	printf("NULL\n");
}

int	main(void)
{
	t_list *lista;
	t_list *nodo1;
    	
    	lista = ft_lstnew("Hola Mundo");
	nodo1 = ft_lstnew("Nodo 1");   
	ft_lstadd_front(&lista, nodo1);    
	print_list(lista);
	free(nodo1);
	return 0;
}
*/
