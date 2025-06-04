/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 09:04:48 by mavellan          #+#    #+#             */
/*   Updated: 2025/06/04 16:44:34 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Actualiza el valor de una variable de entorno existente.
 * Libera el valor anterior y asigna el nuevo.
*/
void	update_existing_env(t_env *curr, const char *value, int has_value)
{
	if (value)
	{
		curr->value = ft_strdup(value);
	}
	else
	{
		curr->value = ft_strdup("");
	}
	curr->has_value = has_value;
}

/*
 * Crea un nuevo nodo de variable de entorno.
 * Lo añade al inicio de la lista enlazada.
*/
void	create_new_env_node(t_env **env, const char *key,
	const char *value, int has_value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("Error al asignar memoria para la nueva variable de entorno");
		return ;
	}
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = ft_strdup("");
	new_node->has_value = has_value;
	new_node->next = *env;
	*env = new_node;
}

/*
 * Añade o actualiza una variable de entorno en la lista
 * Si la variable ya existe, actualiza su valor
 * Si no existe, crea un nuevo nodo al principio de la lista
 * El parámetro has_value indica si la variable tiene un valor asignado
*/
void	add_or_update_env(t_env **env, const char *key,
	const char *value, int has_value)
{
	t_env	*curr;

	if (!key || !*key)
		return ;
	curr = *env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			update_existing_env(curr, value, has_value);
			return ;
		}
		curr = curr->next;
	}
	create_new_env_node(env, key, value, has_value);
}
