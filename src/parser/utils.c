/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:36:32 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/10 13:05:10 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Salta espacios en blanco en la entrada.
 * Avanza el índice hasta encontrar carácter no-espacio.
*/
void	skip_spaces(const char *input, int *i)
{
	while (input[*i] == ' ' || input[*i] == '\t' || input[*i] == '\n' \
		||input[*i] == '\v' || input[*i] == '\f' || input[*i] == '\r')
		(*i)++;
}

/*
 * Guarda un token en el array de tokens.
 * Crea substring y lo almacena en la posición actual.
*/
void	save_token(char **tokens, t_token_state *s, const char *input, int end)
{
	int		len;
	char	*raw;

	len = end - s->start;
	if (len > 0)
	{
		raw = ft_strndup(&input[s->start], len);
		tokens[s->j++] = raw;
	}
}

/*
 * Obtiene el estado de comillas de una cadena.
 * Verifica si hay comillas sin cerrar hasta posición específica.
*/
t_quote_state	get_quote_state(const char *str, int up_to)
{
	t_quote_state	state;
	int				i;

	state.in_single = false;
	state.in_double = false;
	i = 0;
	while (str[i] && (up_to == -1 || i < up_to))
	{
		if (str[i] == '\'' && !state.in_double)
			state.in_single = !state.in_single;
		else if (str[i] == '\"' && !state.in_single)
			state.in_double = !state.in_double;
		i++;
	}
	return (state);
}
