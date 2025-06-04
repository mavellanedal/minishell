/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:55:57 by mavellan          #+#    #+#             */
/*   Updated: 2025/06/04 16:50:27 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Obtiene el valor de la variable PATH del entorno.
 * Retorna el string de PATH o NULL si no existe.
*/
char	*get_path_variable(t_env *env_list)
{
	char	*path_var;

	path_var = NULL;
	while (env_list)
	{
		if (ft_strcmp(env_list->key, "PATH") == 0)
		{
			path_var = env_list->value;
			break ;
		}
		env_list = env_list->next;
	}
	return (path_var);
}

/*
 * Busca un ejecutable en los directorios de PATH.
 * Retorna la ruta completa si lo encuentra, NULL si no.
*/
char	*search_executable_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*full_path;
	size_t	len;

	i = 0;
	while (paths[i])
	{
		len = ft_strlen(paths[i]) + ft_strlen(cmd) + 2;
		full_path = malloc(len);
		if (!full_path)
			break ;
		ft_strcpy(full_path, paths[i]);
		ft_strcat(full_path, "/");
		ft_strcat(full_path, cmd);
		if (access(full_path, X_OK) == 0)
		{
			ft_free(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free(paths);
	return (NULL);
}

/*
 * Busca un comando en PATH dividiendo por ':'.
 * Maneja comandos absolutos/relativos y búsqueda en PATH.
*/
char	*find_command_path(char *cmd, t_env *env_list)
{
	char	*path_var;
	char	**paths;

	path_var = get_path_variable(env_list);
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);
	return (search_executable_in_paths(paths, cmd));
}

/*
 * Obtiene la ruta completa de un comando.
 * Wrapper principal para búsqueda de comandos.
*/
char	*get_full_command_path(char *cmd_name, t_env *env_list)
{
	if (ft_strchr(cmd_name, '/'))
		return (ft_strdup(cmd_name));
	return (find_command_path(cmd_name, env_list));
}
