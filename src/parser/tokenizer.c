/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:16:14 by ebalana-          #+#    #+#             */
/*   Updated: 2025/05/29 12:59:56 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	save_token(char **tokens, t_token_state *s, const char *input, int end, t_env *env)
{
	int		len;
	char	*raw;
	
	(void)env;

	len = end - s->start;
	if (len > 0)
	{
		raw = ft_strndup(&input[s->start], len);
		tokens[s->j++] = raw;
	}
}

void	init_token_state(t_token_state *s, int last_status, t_env *env)
{
	s->i = 0;
	s->j = 0;
	s->start = 0;
	s->last_status = last_status;
	s->env = env;
}

char	**tokenize_input(const char *input, int last_status, t_env *env)
{
	char			**tokens;
	t_token_state	s;
	t_quote_state	q;
	bool			inside_quotes;
	char			quote_char;

	q = get_quote_state(input, -1);
	if (q.in_single || q.in_double)
	{
		ft_printf(UNCLOSED_QUOTES);
		return (NULL);
	}
	tokens = malloc(sizeof(char *) * 1024);
	if (!tokens)
		return (NULL);
	init_token_state(&s, last_status, env);
	
	while (input[s.i])
	{
		// Skip spaces
		while (input[s.i] == ' ')
			s.i++;
		if (!input[s.i])
			break;
			
		s.start = s.i;
		inside_quotes = false;
		quote_char = 0;
		
		// Single token reading - handles quotes and operators together
		while (input[s.i] && (input[s.i] != ' ' || inside_quotes))
		{
			// Handle quote state changes
			if ((input[s.i] == '\'' || input[s.i] == '\"') && !inside_quotes)
			{
				inside_quotes = true;
				quote_char = input[s.i];
				s.i++;
			}
			else if (inside_quotes && input[s.i] == quote_char)
			{
				inside_quotes = false;
				quote_char = 0;
				s.i++;
			}
			// Break on unquoted operators (unless it's the start of token)
			else if (!inside_quotes && (input[s.i] == '|' || input[s.i] == '<' || input[s.i] == '>'))
			{
				// If we're at the start, this is an operator token
				if (s.i == s.start)
				{
					if ((input[s.i] == '<' || input[s.i] == '>') && input[s.i + 1] == input[s.i])
						s.i += 2;
					else
						s.i++;
					break;
				}
				// Otherwise, we hit an operator - stop here
				else
					break;
			}
			else
			{
				s.i++;
			}
		}
		
		save_token(tokens, &s, input, s.i, env);
	}
	
	tokens[s.j] = NULL;
	return (tokens);
}
