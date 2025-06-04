/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:53:45 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/04 16:45:20 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Valida si un identificador es válido para export.
 * Debe empezar con letra/underscore y contener solo alfanuméricos/underscore.
*/
int	is_valid_identifier_export(const char *str)
{
	int	i;

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
 * Imprime las variables de entorno ordenadas alfabéticamente
 * Las variables se imprimen en el formato "declare -x KEY="VALUE""
 * Si has_value = 0, no se muestra el valor
*/
void	print_export_sorted(t_env *env)
{
	int		len;
	t_env	**sort;

	len = get_env_list_len(env);
	if (len == 0)
		return ;
	sort = copy_env_to_array(env, len);
	if (!sort)
		return ;
	sort_env_array(sort, len);
	print_sorted_env(sort, len);
	free(sort);
}

/*
 * Implementación del builtin export
 * Si no hay argumentos, muestra las variables de entorno
 * Si hay argumentos, los añade a las variables de entorno
 */
int	ft_export(char **args, t_env **env)
{
	int		i;
	int		status;

	i = 1;
	status = 0;
	if (!args[1])
		return (print_and_return(env));
	while (args[i])
	{
		if (!is_valid_identifier_export(args[i]))
			status |= handle_invalid_identifier(args[i]);
		else
			status |= handle_export_argument(args[i], env);
		i++;
	}
	return (status);
}
