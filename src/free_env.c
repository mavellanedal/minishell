/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:04:20 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/03 15:21:07 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Libera memoria del array de entorno
 * Libera cada string y luego el array principal
*/
void	free_env_array(char **env_array)
{
	int	i;

	i = 0;
	if (!env_array)
		return ;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

/*
 * Libera toda la lista enlazada de variables de entorno
 * Libera key, value y el nodo en cada iteración
*/
void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}
