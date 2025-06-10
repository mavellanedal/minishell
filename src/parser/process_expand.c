/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:00:57 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/10 15:29:19 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Expande una variable según su tipo ($?, $VAR o $ solo).
 * Retorna la longitud del texto expandido.
*/
int	expand_variable(t_expand_params *params)
{
	params->len = 0;
	if (params->str[*(params->i)] == '?')
		handle_exit_status(params);
	else if (ft_isalpha(params->str[*(params->i)]) || \
		params->str[*(params->i)] == '_')
		handle_named_variable(params);
	else
	{
		params->result[0] = '$';
		params->len = 1;
	}
	return (params->len);
}

/*
 * Finaliza el resultado de expansión.
 * Añade terminador null y maneja operadores entre comillas.
*/
void	finalize_result(t_processing_state *state)
{
	state->result[state->j] = '\0';
	if (state->had_quotes && state->j == 1 && \
		(state->result[0] == '<' || state->result[0] == '>' || \
			state->result[0] == '|'))
	{
		state->result[1] = state->result[0];
		state->result[0] = '\1';
		state->result[2] = '\0';
	}
}

/*
 * Alterna el estado de comillas (simple/doble).
 * Actualiza flags in_single e in_double.
*/
void	toggle_quotes(t_processing_state *state)
{
	if (state->token[state->i] == '\'')
		state->in_single = !state->in_single;
	else if (state->token[state->i] == '\"')
		state->in_double = !state->in_double;
	state->i++;
}

/*
 * Bucle principal de procesamiento de tokens.
 * Maneja escapes, comillas, variables y caracteres normales.
*/
void	process_loop(t_processing_state *state)
{
	while (state->token[state->i])
	{
		if (state->escaped)
			handle_escape(state);
		else if (state->token[state->i] == '\\' && !state->in_single)
		{
			state->escaped = true;
			state->i++;
		}
		else if ((state->token[state->i] == '\'' && !state->in_double) || \
				(state->token[state->i] == '\"' && !state->in_single))
			toggle_quotes(state);
		else if (state->token[state->i] == '$' && !state->in_single)
			handle_variable(state);
		else
		{
			state->result[state->j] = state->token[state->i];
			state->j++;
			state->i++;
		}
	}
}

/*
 * Procesa un token completo con expansiones.
 * Función principal para expandir variables y manejar comillas.
*/
char	*process_token_properly(const char *token, int last_status, t_env *env)
{
	t_processing_state	state;

	state.token = token;
	state.result = malloc(4096);
	state.i = 0;
	state.j = 0;
	state.in_single = false;
	state.in_double = false;
	state.escaped = false;
	state.had_quotes = false;
	state.last_status = last_status;
	state.env = env;
	if (!state.result)
		return (NULL);
	if (token[0] == '\'' || token[0] == '\"')
		state.had_quotes = true;
	process_loop(&state);
	finalize_result(&state);
	return (state.result);
}
