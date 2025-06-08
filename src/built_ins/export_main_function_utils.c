/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_main_function_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 09:17:22 by mavellan          #+#    #+#             */
/*   Updated: 2025/06/04 16:46:19 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Maneja export sin asignación (ej: export VAR).
 * Si la variable no existe, la crea sin valor (has_value = 0).
*/
int	handle_no_assignment(char *arg, t_env **env)
{
	t_env	*curr;
	int		found;

	curr = *env;
	found = 0;
	while (curr && !found)
	{
		if (ft_strcmp(curr->key, arg) == 0)
			found = 1;
		curr = curr->next;
	}
	if (!found)
		add_or_update_env(env, arg, "", 0);
	return (0);
}

/*
 * Maneja export con asignación (ej: export VAR=value).
 * Separa clave y valor, añade/actualiza la variable.
*/
int	handle_assignment(char *arg, t_env **env)
{
	char	*eq;
	char	*key;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return (0);
	*eq = '\0';
	key = ft_strdup(arg);
	add_or_update_env(env, key, eq + 1, 1);
	*eq = '=';
	free(key);
	return (0);
}

/*
 * Maneja identificadores inválidos en export.
 * Muestra error y retorna código de error.
*/
int	handle_invalid_identifier(char *arg)
{
	printf("minishell: export: `%s`: not a valid identifier\n", arg);
	return (1);
}

/*
 * Imprime variables de entorno ordenadas y retorna 0.
 * Función auxiliar para export sin argumentos.
*/
int	print_and_return(t_env **env)
{
	print_export_sorted(*env);
	return (0);
}

/*
 * Procesa un argumento de export.
 * Detecta si es asignación o declaración simple.
*/
int	handle_export_argument(char *arg, t_env **env)
{
	if (ft_strchr(arg, '='))
		return (handle_assignment(arg, env));
	return (handle_no_assignment(arg, env));
}
