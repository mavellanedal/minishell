/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:47:09 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/30 16:45:31 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current -> next)
	{
		current = current -> next;
	}
	current -> next = new;
}
/*
#include <stdio.h>

void    print_list(t_list *lst)
{
    while (lst)
    {
        printf("%d -> ", *(int *)(lst->content));
        lst = lst->next;
    }
    printf("NULL\n");
}

int main(void)
{
    // Variables para los datos
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;

    // Crear los nodos de la lista
    t_list *node1 = ft_lstnew(&data1);
    t_list *node2 = ft_lstnew(&data2);
    t_list *node3 = ft_lstnew(&data3);

    // Inicializamos la lista con el primer nodo
    t_list *lst = node1;

    // Añadir node2 al final de la lista
    ft_lstadd_back(&lst, node2);

    // Añadir node3 al final de la lista
    ft_lstadd_back(&lst, node3);

    // Imprimir la lista para verificar
    printf("Lista después de añadir nodos:\n");
    print_list(lst);

    // Liberar la memoria de los nodos (opcional pero recomendado)
    // Aquí asumimos que el contenido no necesita ser liberado
    free(node1);
    free(node2);
    free(node3);

    return 0;
}
*/
