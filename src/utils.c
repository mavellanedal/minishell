/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:10:41 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/24 17:03:46 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
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
	printf("exit\n");
	if (args[1])
	{
		if (!ft_isnumber(args[1]))
		{
			printf("exit: %s: numeric argument required\n", args[1]);
			exit(255);
		}
		if (args[2])
		{
			printf("exit: too many arguments\n");
			return (1);
		}
		exit(ft_atoi(args[1]) % 256);
	}
	exit(0);
}

int	execute_builtin(char **args)
{
	if (!args || !args[0])
		return (-1);
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args));
	return (-1);
}
