/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:36:32 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/04 13:40:16 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	skip_spaces(const char *input, int *i)
{
	while (input[*i] == ' ')
		(*i)++;
}

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
