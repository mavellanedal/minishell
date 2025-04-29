/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:10:41 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/29 18:07:24 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_echo(char **args)
{
	int	i;
	int	newline;
	
	i = 1;
	newline = 1;
	while (args[i] && args[i][0] == '-' && ft_strncmp(args[i], "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

int	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd");
	return (0);
}

int	ft_exit(char **args)
{
	int	exit_code;
	if (args[1])
	{
		exit_code = ft_atoi(args[1]);
		if (exit_code < 0)
			exit_code = 255;
	}
	else
		exit_code = 0;
	printf("exit\n");
	exit(exit_code);
}

t_env *create_env_list(char **envp)
{
	t_env	*head;
	t_env	*node;
	int		i;
	
	head = NULL;
	i = 0;
	while (envp[i])
	{
		char **split = ft_split(envp[i], '=');
		node = malloc(sizeof(t_env));
		node->key = strdup(split[0]);
		node->value = strdup(split[1] ? split[1] : "");
		node->next = head;
		head = node;
		free(split[0]);
		if (split[1]) free(split[1]);
		free(split);
		i++;
	}
	return (head);
}

int ft_env(t_env *env_list)
{
    while (env_list)
    {
        if (env_list->value)
            printf("%s=%s\n", env_list->key, env_list->value);
        env_list = env_list->next;
    }
    return (0);
}

int execute_builtin(char **args, t_env *env_list)
{
	if (!args || !args[0])
		return (-1);
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args));
	if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(env_list));
	return (-1);
}
