/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:55:57 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/27 17:58:22 by mavellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_path_variable(t_env *env_list)
{
	char	*path_var;

	path_var = NULL;
	while (env_list)
	{
		if (ft_strcmp(env_list->key, "PATH") == 0)
		{
			path_var = env_list->value;
			break;
		}
		env_list = env_list->next;
	}
	return (path_var);
}

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
			break;
		sprintf(full_path, "%s/%s", paths[i], cmd);
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

char	*get_full_command_path(char *cmd_name, t_env *env_list)
{
	if (ft_strchr(cmd_name, '/'))
		return (strdup(cmd_name));
	return (find_command_path(cmd_name, env_list));
}
