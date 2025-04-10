/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:46:23 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/30 14:13:11 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
	{
		lst = lst -> next;
	}
	return (lst);
}
/*
#include <stdio.h>

void	ft_lstprint(t_list *lst) 
{
	while (lst) 
	{
		printf("%d -> ", *(int *)(lst->content));
		lst = lst->next;
	}
	printf("NULL\n");
}

int	main()
{

	int *val1 = malloc(sizeof(int));
	*val1 = 1;
	t_list *nodo1 = ft_lstnew(val1);

	int *val2;
	val2 = malloc(sizeof(int));
	if (val2 != NULL)
		*val2 = 2;
	t_list *nodo2 = ft_lstnew(val2);

	int *val3 = malloc(sizeof(int));
	*val3 = 3;
	t_list *nodo3 = ft_lstnew(val3);

	nodo1->next = nodo2;
	nodo2->next = nodo3;
    
	printf("Lista original: ");
	ft_lstprint(nodo1);

	t_list *ultimo = ft_lstlast(nodo1);
	printf("Posicion ultimo nodo: %d\n", *(int *)(ultimo->content));


	int *val4 = malloc(sizeof(int));
	*val4 = 4;
	t_list *nuevo_nodo = ft_lstnew(val4);
	ultimo->next = nuevo_nodo;

	printf("Lista después de añadir un nuevo nodo: ");
	ft_lstprint(nodo1);

	ultimo = ft_lstlast(nodo1);
	printf("Posicion ultimo nodo: %d\n", *(int *)(ultimo->content));

	free(val1);
	free(val2);
	free(val3);
	free(val4);
	free(nodo1);
	free(nodo2);
	free(nodo3);
	free(nuevo_nodo);

	return 0;
}
*/
