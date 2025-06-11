/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:10:41 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/11 13:50:26 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Implementación del builtin echo.
 * Imprime argumentos con opción -n para suprimir newline.
*/
int	ft_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i] && ft_is_echo_n_flag(args[i]))
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

/*
 * Implementación del builtin pwd.
 * Muestra el directorio de trabajo actual.
*/
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

/*
 * Implementación del builtin exit.
 * Termina el shell con código de salida opcional.
*/
int	ft_exit(char **args)
{
	int		arg_count;
	long	code;

	arg_count = 0;
	while (args[arg_count])
		arg_count++;
	if (arg_count > 1)
	{
		if (!ft_is_numeric(args[1]) || ft_is_too_long_numeric(args[1]))
		{
			printf("minishell: exit: %s: numeric argument required\n", args[1]);
			exit(2);
		}
		if (arg_count > 2)
		{
			printf("minishell: exit: too many arguments\n");
			return (1);
		}
		code = ft_atoi(args[1]);
		exit((unsigned char)code);
	}
	exit(0);
}

/*
 * Implementación del builtin unset.
 * Elimina variables de entorno validando identificadores.
*/
int	ft_unset(char **args, t_env **env_list)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			printf(UNSET, args[i]);
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
 * Ejecuta el builtin correspondiente según el comando.
 * Dispatcher principal para todos los builtins del shell.
*/
int	execute_builtin(char **args, t_env **env_list)
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
			printf(ENV, args[1]);
			return (127);
		}
		return (ft_env(*env_list));
	}
	if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(args, env_list));
	if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args, env_list));
	if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(args, env_list));
	return (-1);
}
