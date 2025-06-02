/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:41:34 by mavellan          #+#    #+#             */
/*   Updated: 2025/06/02 15:18:28 by ebalana-         ###   ########.fr       */
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
			len = ft_strlen(env->key) + ft_strlen(env->value) + 2;
			entry = malloc(len);
			if (!entry)
			{
				free_partial_envp(envp, i);
				return (-1);
			}
			ft_strcpy(entry, env->key);
			ft_strcat(entry, "=");
			ft_strcat(entry, env->value);
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

int	count_env_vars(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->value)
			count++;
		env = env->next;
	}
	return (count);
}
