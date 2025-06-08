/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes_redirecctions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:56:25 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/04 17:04:46 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Verifica si un token es un operador de redirección.
 * Detecta <, >, >>, <<.
*/
bool	operator_check(char *token)
{
	if (!token)
		return (false);
	if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0 || \
		ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<<") == 0)
		return (true);
	return (false);
}

/*
 * Valida operadores inválidos como >>>, <<<<, ><, <>.
 * Retorna 1 si encuentra error, 0 si es válido.
*/
int	validate_invalid_operators(char *token)
{
	if (ft_strncmp(token, ">>>", 3) == 0)
	{
		printf("minishell: syntax error near unexpected token `>'\n");
		return (1);
	}
	if (ft_strncmp(token, "<<<<", 4) == 0)
	{
		printf("minishell: syntax error near unexpected token `<'\n");
		return (1);
	}
	if ((ft_strncmp(token, "><", 2) == 0) || (ft_strncmp(token, "<>", 2) == 0))
	{
		printf("minishell: syntax error near unexpected token`%c'\n", token[1]);
		return (1);
	}
	return (0);
}

/*
 * Valida sintaxis de redirecciones.
 * Verifica que después del operador haya un archivo válido.
*/
int	validate_redirection_syntax(char **tokens, int i)
{
	if (!operator_check(tokens[i]))
		return (0);
	if (!tokens[i + 1])
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		return (1);
	}
	if (operator_check(tokens[i + 1]) || ft_strcmp(tokens[i + 1], "|") == 0)
	{
		printf("minishell: syntax error near unexpected token `%s'\n", \
		tokens[i + 1]);
		return (1);
	}
	return (0);
}

/*
 * Valida sintaxis de pipes.
 * Detecta pipes al final o consecutivos.
*/
int	validate_pipe_syntax(char **tokens, int i)
{
	if (ft_strcmp(tokens[i], "|") != 0)
		return (0);
	if (!tokens[i + 1] || ft_strcmp(tokens[i + 1], "|") == 0)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

/*
 * Función principal de validación de sintaxis.
 * Verifica pipes, redirecciones y operadores inválidos.
*/
int	validate_syntax(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (validate_pipe_syntax(tokens, i))
			return (2);
		if (validate_redirection_syntax(tokens, i))
			return (2);
		if (validate_invalid_operators(tokens[i]))
			return (2);
		i++;
	}
	return (0);
}
