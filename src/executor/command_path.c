/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:55:57 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/17 17:41:48 by mavellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_command_path(char *cmd, t_env *env_list)
{
	char	*path_var = NULL;
	char	**paths;
	char	*full_path;
	int		i;

	// Obtener PATH de env_list
	while (env_list)
	{
		if (ft_strcmp(env_list->key, "PATH") == 0)
		{
			path_var = env_list->value;
			break;
		}
		env_list = env_list->next;
	}
	if (!path_var)
		return (NULL);

	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);

	i = 0;
	while (paths[i])
	{
		full_path = malloc(ft_strlen(paths[i]) + ft_strlen(cmd) + 2);
		if (!full_path)
			break;
		sprintf(full_path, "%s/%s", paths[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			ft_free(paths);
			return (full_path); // Encontrado
		}
		free(full_path);
		i++;
	}
	ft_free(paths);
	return (NULL);
}