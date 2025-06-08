/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:33:10 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/04 16:43:51 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Crea un nodo de entorno a partir de una cadena del formato "KEY=VALUE"
 * Actualizada para manejar el campo has_value
*/
t_env	*create_node_env(char *env_var)
{
	t_env	*node;
	char	*equal_sign;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	equal_sign = ft_strchr(env_var, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		node->key = ft_strdup(env_var);
		node->value = ft_strdup(equal_sign + 1);
		node->has_value = 1;
		*equal_sign = '=';
	}
	else
	{
		node->key = ft_strdup(env_var);
		node->value = ft_strdup("");
		node->has_value = 0;
	}
	node->next = NULL;
	return (node);
}

/*
 * Crea la lista enlazada de entorno desde el array envp del sistema.
 * Todas las variables tienen has_value = 1 por defecto.
*/
t_env	*create_env_list(char **envp)
{
	t_env	*head;
	t_env	*node;
	int		i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		node = create_node_env(envp[i]);
		if (node)
		{
			node->has_value = 1;
			node->next = head;
			head = node;
		}
		i++;
	}
	return (head);
}

/*
 * Implementación del builtin env.
 * Muestra solo variables con has_value = 1.
*/
int	ft_env(t_env *env_list)
{
	while (env_list)
	{
		if (env_list->has_value)
			printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
	return (0);
}

/*
 * Valida si un identificador es válido para variables de entorno.
 * Debe empezar con letra/underscore y contener solo alfanuméricos/underscore.
*/
int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0] || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/*
 * Elimina una variable de entorno por su clave.
 * Libera memoria del nodo eliminado.
*/
void	remove_env_key(t_env **env_list, const char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env_list;
	prev = NULL;
	while (curr)
	{
		if (curr->key && ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env_list = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
