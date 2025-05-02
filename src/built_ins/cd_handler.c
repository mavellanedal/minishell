/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:52:32 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/30 16:47:06 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	update_env_var(t_env *env, const char *key, const char *new_value)
{
	t_env	*current;
	t_env	*new_node;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(new_value);
			return ;
		}
		if (!current->next)
			break ;
		current = current->next;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(new_value);
	new_node->next = NULL;
	current->next = new_node;
}

char	*get_cd_target(char **args, t_env *env)
{
	char	*target;

	if (!args[1])
	{
		target = get_env_value(env, "HOME");
		if (!target)
			fprintf(stderr, "cd: HOME not set\n");
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		target = get_env_value(env, "OLDPWD");
		if (!target)
			fprintf(stderr, "cd: OLDPWD not set\n");
		else
			printf("%s\n", target);
	}
	else
		target = args[1];
	return (target);
}

void	update_pwd_vars(t_env *env, char *oldpwd)
{
	char	*cwd;

	if (oldpwd)
		update_env_var(env, "OLDPWD", oldpwd);
	free(oldpwd);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		update_env_var(env, "PWD", cwd);
		free(cwd);
	}
}

int	ft_cd(char **args, t_env *env)
{
	char	*target;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	target = get_cd_target(args, env);
	if (!target)
	{
		free(oldpwd);
		return (1);
	}
	if (chdir(target) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	update_pwd_vars(env, oldpwd);
	return (0);
}
