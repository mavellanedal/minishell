/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:35:11 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/30 12:48:23 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lstnew;

	lstnew = (t_list *)malloc(sizeof(t_list));
	if (!lstnew)
		return (NULL);
	lstnew -> content = content;
	lstnew -> next = NULL;
	return (lstnew);
}
/*
#include <stdio.h>

int	main()
{
	t_list	*new;
	
	new = ft_lstnew("Hola Mundo");

	if (new != NULL)
		printf("El nuevo contenido es: %s\n", (char *)new -> content);
	free(new);
	return (0);
}
*/
