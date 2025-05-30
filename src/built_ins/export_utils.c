/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 09:12:35 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/30 21:51:07 by mavellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_env_list_len(t_env *env)
{
	int		len;
	t_env	*tmp;

	len = 0;
	tmp = env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

t_env	**copy_env_to_array(t_env *env, int len)
{
	t_env	**arr;
	t_env	*tmp;
	int		i;

	arr = malloc(sizeof(t_env *) * len);
	if (!arr)
	{
		perror("Error allocating memory to sort variables");
		return (NULL);
	}
	tmp = env;
	i = 0;
	while (tmp)
	{
		arr[i] = tmp;
		tmp = tmp->next;
		i++;
	}
	return (arr);
}

void	sort_env_array(t_env **arr, int len)
{
	int		i;
	int		j;
	t_env	*swap;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(arr[j]->key, arr[j + 1]->key) > 0)
			{
				swap = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = swap;
			}
			j++;
		}
		i++;
	}
}

void	print_sorted_env(t_env **arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (ft_strcmp(arr[i]->key, "_") != 0)
		{
			printf("declare -x %s", arr[i]->key);
			if (arr[i]->has_value)
				printf("=\"%s\"", arr[i]->value);
			printf("\n");
		}
		i++;
	}
}
