/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:53:45 by ebalana-          #+#    #+#             */
/*   Updated: 2025/05/02 18:35:50 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_identifier_export(const char *str)
{
	int i = 0;

	if (!str || !str[0])
		return (0);
	if (!isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

// void	add_or_update_env(t_env **env, const char *key, const char *value)
// {
// 	t_env	*curr = *env;

// 	while (curr)
// 	{
// 		if (strcmp(curr->key, key) == 0)
// 		{
// 			// Ya existe: actualizar valor
// 			free(curr->value);
// 			curr->value = value ? strdup(value) : NULL;
// 			return;
// 		}
// 		curr = curr->next;
// 	}

// 	// No existe: crear nuevo nodo
// 	t_env *new = malloc(sizeof(t_env));
// 	if (!new)
// 		return;
// 	new->key = strdup(key);
// 	new->value = value ? strdup(value) : NULL;
// 	new->next = *env;
// 	*env = new;
// }

void	add_or_update_env(t_env **env, const char *key, const char *value)
{
	t_env *curr = *env;

	// Revisar si ya existe la variable
	while (curr)
	{
		if (strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			curr->value = value ? strdup(value) : NULL;
			printf("DEBUG: Variable '%s' actualizada a '%s'\n", key, value);
			return;
		}
		curr = curr->next;
	}

	// Si no existe, creamos un nuevo nodo
	t_env *new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("Error al asignar memoria para la nueva variable de entorno");
		return;
	}
	new_node->key = strdup(key);
	new_node->value = value ? strdup(value) : NULL;
	new_node->next = *env;
	*env = new_node;

	// Verificación de la adición
	printf("DEBUG: Variable '%s' añadida con valor '%s'\n", key, value);
}


void	print_export_sorted(t_env *env)
{
	int i = 0, len = 0;
	t_env *tmp;

	// Contar cuántas variables hay
	tmp = env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	if (len == 0)
	{
		printf("No hay variables de entorno.\n");
		return;
	}
	// Array para ordenarlas
	t_env **arr = malloc(sizeof(t_env *) * len);
	tmp = env;
	while (tmp)
	{
		arr[i++] = tmp;
		tmp = tmp->next;
	}
	// Orden burbuja por clave
	for (i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - i - 1; j++)
		{
			if (strcmp(arr[j]->key, arr[j + 1]->key) > 0)
			{
				t_env *swap = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = swap;
			}
		}
	}
	// Imprimir las variables de entorno ordenadas
	for (i = 0; i < len; i++)
	{
		printf("%s=%s\n", arr[i]->key, arr[i]->value ? arr[i]->value : "(null)");
	}
	printf("------------------------------------\n");
	printf("Variables: %d\n", len);  // Mostrar el número de variables
	printf("------------------------------------\n");
	free(arr);
}

int	ft_export(char **args, t_env **env)
{
    int i = 1;

    // Si no hay argumentos (solo `export`), mostramos las variables de entorno
    if (!args[1]) 
    {
        print_export_sorted(*env);  // Llama a la función de impresión de variables
        return (0);
    }

    // Si hay argumentos (por ejemplo `export TEST1=HELLO`)
    while (args[i])
    {
        if (!is_valid_identifier_export(args[i]))
        {
            fprintf(stderr, "export: `%s`: not a valid identifier\n", args[i]);
            i++;
            continue;
        }

        char *eq = strchr(args[i], '=');
        if (eq)
        {
            // Si hay un `=`, separamos la clave y el valor
            char *key = strndup(args[i], eq - args[i]);
            char *value = strdup(eq + 1);
            add_or_update_env(env, key, value);  // Añadimos o actualizamos la variable
            free(key);
            free(value);
        }
        else
        {
            // Si no hay un `=`, solo añadimos la clave sin valor
            add_or_update_env(env, args[i], NULL);
        }
        i++;
    }
	save_env_to_file(*env);
	load_env_from_file(env);
    // // Imprimir las variables después de añadir o actualizar
    // printf("Variables después de añadir:\n");
    // print_export_sorted(*env);  // Verificar que la variable se ha añadido correctamente
    return (0);
}
