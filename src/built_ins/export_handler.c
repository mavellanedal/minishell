/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:53:45 by ebalana-          #+#    #+#             */
/*   Updated: 2025/05/20 15:42:12 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Comprueba si un identificador es válido para export
*/
int	is_valid_identifier_export(const char *str)
{
	int i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/*
 * Añade o actualiza una variable de entorno en la lista
 * Si la variable ya existe, actualiza su valor
 * Si no existe, crea un nuevo nodo al principio de la lista
 * El parámetro has_value indica si la variable tiene un valor asignado
*/
void	add_or_update_env(t_env **env, const char *key, const char *value, int has_value)
{
	t_env	*curr;

	curr = *env;
	// Comprobar si la clave es NULL o vacía
	if (!key || !*key)
		return ;
	// Revisar si ya existe la variable
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			// Actualizar valor existente
			free(curr->value);
			curr->value = value ? ft_strdup(value) : ft_strdup("");
			curr->has_value = has_value;
			return ;
		}
		curr = curr->next;
	}
	// Si no existe, creamos un nuevo nodo
	t_env *new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("Error al asignar memoria para la nueva variable de entorno");
		return ;
	}
	new_node->key = ft_strdup(key);
	new_node->value = value ? ft_strdup(value) : ft_strdup("");
	new_node->has_value = has_value;
	new_node->next = *env;
	*env = new_node;
}

/*
 * Imprime las variables de entorno ordenadas alfabéticamente
 * Las variables se imprimen en el formato "declare -x KEY="VALUE""
 * Si has_value = 0, no se muestra el valor
 */
void	print_export_sorted(t_env *env)
{
	int		i;
	int		len;
	t_env	*tmp;
	t_env	**sort;

	i = 0;
	len = 0;
	// Contar cuántas variables hay
	tmp = env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	if (len == 0)
		return ;
	// Array para ordenarlas
	sort = malloc(sizeof(t_env *) * len);
	if (!sort)
	{
		perror("Error allocating memory to sort variables");
		return ;
	}
	tmp = env;
	i = 0;
	while (tmp)
	{
		sort[i++] = tmp;
		tmp = tmp->next;
	}
	// Orden burbuja por clave
	for (i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - i - 1; j++)
		{
			if (ft_strcmp(sort[j]->key, sort[j + 1]->key) > 0)
			{
				t_env *swap = sort[j];
				sort[j] = sort[j + 1];
				sort[j + 1] = swap;
			}
		}
	}
	// Imprimir las variables de entorno ordenadas en formato bash
	for (i = 0; i < len; i++)
	{
		if (ft_strcmp(sort[i]->key, "_") == 0)
			continue;
		printf("declare -x %s", sort[i]->key);
		if (sort[i]->has_value)  // Solo mostramos el valor si has_value es 1
			printf("=\"%s\"", sort[i]->value);
		printf("\n");
	}
	free(sort);
}

/*
 * Implementación del builtin export
 * Si no hay argumentos, muestra las variables de entorno
 * Si hay argumentos, los añade a las variables de entorno
 */
int	ft_export(char **args, t_env **env)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	ft_printf("------------ BUILT IN - EXPORT ------------\n");
	// Si no hay argumentos (solo `export`), mostramos las variables de entorno
	if (!args[1]) 
	{
		print_export_sorted(*env);
		return (0);
	}
	// Si hay argumentos (por ejemplo `export TEST1=HELLO`)
	while (args[i])
	{
		if (!is_valid_identifier_export(args[i]))
		{
			fprintf(stderr, "export: `%s`: not a valid identifier\n", args[i]);
			status = 1;
			i++;
			continue;
		}
		char *eq = strchr(args[i], '=');
		if (eq)
		{
			// Si hay un `=`, separamos la clave y el valor
			*eq = '\0'; // Separamos temporalmente la cadena
			add_or_update_env(env, args[i], eq + 1, 1);  // has_value = 1
			*eq = '='; // Restauramos la cadena original
		}
		else
		{
			// Si no hay un `=`, solo añadimos la clave sin valor si no existe
			// Si ya existe, mantenemos su valor actual y su estado has_value
			t_env *curr = *env;
			int exists = 0;			
			while (curr && !exists)
			{
				if (ft_strcmp(curr->key, args[i]) == 0)
					exists = 1;
				curr = curr->next;
			}
			if (!exists)
				add_or_update_env(env, args[i], "", 0);  // has_value = 0
		}
		i++;
	}
	return (status);
}
