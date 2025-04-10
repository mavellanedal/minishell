/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:49:23 by ebalana-          #+#    #+#             */
/*   Updated: 2024/10/01 17:55:06 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*new;

	if (!f || !del)
		return (NULL);
	first = NULL;
	while (lst)
	{
		new = ft_lstnew((*f)(lst->content));
		if (!(new))
		{
			while (first)
			{
				new = first->next;
				(*del)(first->content);
				free(first);
				first = new;
			}
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&first, new);
		lst = lst->next;
	}
	return (first);
}
/*
#include <stdio.h>

void    *duplicate_content(void *content)
{
    return (ft_strdup((char *)content));
}

void    print_content(void *content)
{
    printf("Nodo: %s\n", (char *)content);
}

void    del(void *content)
{
    free(content);
}

int	main(void)
{
	t_list	*list = NULL;
	t_list	*new_list = NULL;
	
	ft_lstadd_back(&list, ft_lstnew(ft_strdup("Nodo 1")));
	ft_lstadd_back(&list, ft_lstnew(ft_strdup("Nodo 2")));
	ft_lstadd_back(&list, ft_lstnew(ft_strdup("Nodo 3")));


	printf("Contenido de la lista original:\n");
	ft_lstiter(list, print_content);

	new_list = ft_lstmap(list, duplicate_content, del);

	if (new_list)
	{
		printf("\nContenido de la nueva lista 
		(después de aplicar ft_lstmap):\n");
		ft_lstiter(new_list, print_content);
	}

	ft_lstclear(&list, del);
	ft_lstclear(&new_list, del);

	return (0);
}
*/
