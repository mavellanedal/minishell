/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:44:21 by ebalana-          #+#    #+#             */
/*   Updated: 2024/10/01 17:12:22 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*nlst;
	t_list	*plst;

	if (!lst || !del)
		return ;
	nlst = *lst;
	while (nlst)
	{
		plst = nlst -> next;
		del(nlst -> content);
		free(nlst);
		nlst = plst;
	}
	*lst = NULL;
}
/*
void	del(void *content)
{
	free(content);
}

#include <stdio.h>

void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("Content: %s\n", (char *)lst->content);
		lst = lst->next;
	}
}

int	main(void)
{
	t_list *list = NULL;

	ft_lstadd_back(&list, ft_lstnew(ft_strdup("Nodo 1")));
	ft_lstadd_back(&list, ft_lstnew(ft_strdup("Nodo 2")));
	ft_lstadd_back(&list, ft_lstnew(ft_strdup("Nodo 3")));

	printf("Antes del CLEAN: \n");
	print_list(list);

	ft_lstclear(&list, del);
	printf("Despues del CLEAN:\n");
	if (!list)
		printf("Content: NULL \n");
	return (0);
}
*/
