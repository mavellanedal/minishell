/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:10:41 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/30 14:04:38 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		printf("%s\n", cwd);
		free(cwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
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

int	ft_unset(char **args, t_env **env_list)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			fprintf(stderr, UNSET, args[i]);
		}
		else
		{
			remove_env_key(env_list, args[i]);
		}
		i++;
	}
	return (0);
}

/*
127 → comando no encontrado.
126 → comando encontrado pero no ejecutable (por ejemplo, sin permisos).
1 → error genérico.
0 → todo OK.
*/
int	execute_builtin(char **args, t_env *env_list)
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
	{
		if (args[1] != NULL)
		{
			fprintf(stderr, ENV, args[1]);
			return (127);
		}
		return (ft_env(env_list));
	}
	if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(args, &env_list));
	return (-1);
}
