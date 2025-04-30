/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:33:10 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/30 13:52:17 by ebalana-         ###   ########.fr       */
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

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0] || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	remove_env_key(t_env **env_list, const char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env_list;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env_list = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
