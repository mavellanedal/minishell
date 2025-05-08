/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:41:34 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/02 13:53:44 by mavellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**convert_env_to_envp(t_env *env)
{
	char	**envp;
	int		size;
	int		result;

	size = count_env_vars(env);
	envp = malloc((size + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	result = fill_envp_array(env, envp);
	if (result == -1)
		return (NULL);
	envp[result] = NULL;
	return (envp);
}

int	fill_envp_array(t_env *env, char **envp)
{
	int		i;
	size_t	len;
	char	*entry;

	i = 0;
	while (env)
	{
		if (env->value)
		{
			len = strlen(env->key) + strlen(env->value) + 2;
			entry = malloc(len);
			if (!entry)
			{
				free_partial_envp(envp, i);
				return (-1);
			}
			strcpy(entry, env->key);
			strcat(entry, "=");
			strcat(entry, env->value);
			envp[i] = entry;
			i++;
		}
		env = env->next;
	}
	return (i);
}

char	**free_partial_envp(char **envp, int until)
{
	int	i;

	i = until - 1;
	while (i >= 0)
	{
		free(envp[i]);
		i--;
	}
	free(envp);
	return (NULL);
}

