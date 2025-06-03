/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:00:53 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/03 14:02:52 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Incrementa SHLVL si ya existe en la lista de entorno.
 * Retorna 1 si fue encontrada y actualizada, 0 si no.
*/
int	increment_shlvl_if_exists(t_env *env)
{
	int	new_level;

	while (env)
	{
		if (ft_strcmp(env->key, "SHLVL") == 0)
		{
			new_level = 1;
			if (env->value && *(env->value))
				new_level = ft_atoi(env->value) + 1;
			free(env->value);
			env->value = ft_itoa(new_level);
			env->has_value = 1;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

/*
 * Añade un nuevo nodo SHLVL=1 al inicio de la lista de entorno.
*/
void	add_shlvl_node(t_env **env_list)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = ft_strdup("SHLVL");
	new_node->value = ft_strdup("1");
	new_node->has_value = 1;
	new_node->next = *env_list;
	*env_list = new_node;
}

/*
 * Actualiza o inicializa la variable de entorno SHLVL.
*/
void	update_shlvl(t_env **env_list)
{
	if (!increment_shlvl_if_exists(*env_list))
		add_shlvl_node(env_list);
}
