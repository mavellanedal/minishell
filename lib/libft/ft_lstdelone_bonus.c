/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:02:07 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/30 17:15:48 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del (lst -> content);
	free (lst);
}
/*
#include <stdio.h>

void    del_content(void *content)
{
	(void)content;
}
int	main()
{
	char	*content = "Hola";

	t_list	*node = ft_lstnew(content);
	printf("Contenido antes de eliminar: %s\n", (char *)node->content);
	ft_lstdelone(node, del_content);
	printf("Contenido eliminado");
	return (0);
}
*/
