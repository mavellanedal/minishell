/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:38:07 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/04 17:05:40 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Maneja caracteres escapados en expansión de tokens.
 * Procesa escapes según el contexto de comillas.
*/
void	handle_escape(t_processing_state *state)
{
	char	c;

	c = state->token[state->i];
	if (state->in_double && (c == '$' || c == '\"' || c == '\\' || c == '\n'))
		state->result[state->j++] = c;
	else if (!state->in_single && !state->in_double)
		state->result[state->j++] = c;
	else
	{
		state->result[state->j++] = '\\';
		state->result[state->j++] = c;
	}
	state->escaped = false;
	state->i++;
}

/*
 * Maneja expansión de variables ($VAR, $?).
 * Configura parámetros y llama a expand_variable.
*/
void	handle_variable(t_processing_state *state)
{
	t_expand_params	params;

	params.str = state->token;
	params.i = &state->i;
	params.result = state->result + state->j;
	params.last_status = state->last_status;
	params.env = state->env;
	params.len = 0;
	state->i++;
	state->j += expand_variable(&params);
}

/*
 * Maneja expansión de código de salida ($?).
 * Convierte last_status a string y lo copia al resultado.
*/
void	handle_exit_status(t_expand_params *params)
{
	char	*status_str;

	status_str = ft_itoa(params->last_status);
	if (!status_str)
		return ;
	ft_strcpy(params->result, status_str);
	params->len = ft_strlen(status_str);
	free(status_str);
	(*params->i)++;
}

/*
 * Maneja expansión de variables de entorno ($VAR).
 * Busca la variable en env y copia su valor.
*/
void	handle_named_variable(t_expand_params *params)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = *(params->i);
	while (ft_isalnum(params->str[*(params->i)]) || \
		params->str[*(params->i)] == '_')
		(*params->i)++;
	var_name = ft_substr(params->str, start, *(params->i) - start);
	if (!var_name)
		return ;
	var_value = get_env_value(params->env, var_name);
	if (var_value)
	{
		ft_strcpy(params->result, var_value);
		params->len = ft_strlen(var_value);
	}
	free(var_name);
}
