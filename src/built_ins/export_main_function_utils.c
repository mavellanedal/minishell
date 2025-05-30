/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_main_function_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 09:17:22 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/30 21:46:21 by mavellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	handle_assignment(char *arg, t_env **env)
{
	char	*eq;
	char	*key;

	eq = strchr(arg, '=');
	if (!eq)
		return (0);
	*eq = '\0';
	key = ft_strdup(arg);
	add_or_update_env(env, key, eq + 1, 1);
	*eq = '=';
	free(key);
	return (0);
}

int	handle_invalid_identifier(char *arg)
{
	fprintf(stderr, "export: `%s`: not a valid identifier\n", arg);
	return (1);
}

int	print_and_return(t_env **env)
{
	print_export_sorted(*env);
	return (0);
}

int	handle_export_argument(char *arg, t_env **env)
{
	if (strchr(arg, '='))
		return (handle_assignment(arg, env));
	return (handle_no_assignment(arg, env));
}
