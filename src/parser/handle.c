/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:38:07 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/02 13:00:00 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	state->j += expand_variable_here(&params);
}
