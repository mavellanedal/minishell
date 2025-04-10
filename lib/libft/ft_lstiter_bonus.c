/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:31:19 by ebalana-          #+#    #+#             */
/*   Updated: 2024/10/01 17:41:12 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst -> content);
		lst = lst -> next;
	}
}
/*
#include <stdio.h>

void    print_content(void *content)
{
    printf("Nodo: %s\n", (char *)content);
}

int	main(void)
{
	t_list	*list = NULL;

	ft_lstadd_back(&list, ft_lstnew(ft_strdup("Nodo 1")));
	ft_lstadd_back(&list, ft_lstnew(ft_strdup("Nodo 2")));
	ft_lstadd_back(&list, ft_lstnew(ft_strdup("Nodo 3")));

	printf("Contenido de la lista:\n");
	ft_lstiter(list, print_content);
	
	// ft_lstclear(&list, del);

	return (0);
}
*/
