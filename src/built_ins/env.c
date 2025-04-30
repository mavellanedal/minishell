/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:33:10 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/30 13:08:12 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*create_node_env(char *env_var)
{
	t_env	*node;
	char	**split;

	split = ft_split(env_var, '=');
	if (!split || !split[0])
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(split[0]);
	if (split[1])
		node->value = ft_strdup(split[1]);
	else
		node->value = ft_strdup("");
	free(split[0]);
	if (split[1])
		free(split[1]);
	free(split);
	return (node);
}

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
			node->next = head;
			head = node;
		}
		i++;
	}
	return (head);
}

int	ft_env(t_env *env_list)
{
	while (env_list)
	{
		if (env_list->value)
			printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
	return (0);
}
