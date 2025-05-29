/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:16:14 by ebalana-          #+#    #+#             */
/*   Updated: 2025/05/29 12:48:43 by ebalana-         ###   ########.fr       */
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

void	handle_quotes(const char *input, t_token_state *s)
{
	char	quote_char;

	quote_char = input[s->i];
	s->i++; // Skip opening quote
	while (input[s->i] && input[s->i] != quote_char)
		s->i++;
	if (input[s->i] == quote_char)
		s->i++; // Skip closing quote
}

char	**tokenize_input(const char *input, int last_status, t_env *env)
{
	char			**tokens;
	t_token_state	s;
	t_quote_state	q;

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
		
		// Check for redirection operators FIRST (only outside quotes)
		if ((input[s.i] == '|' || input[s.i] == '<' || input[s.i] == '>') && 
			input[s.i] != '\'' && input[s.i] != '\"')
		{
			if ((input[s.i] == '<' || input[s.i] == '>') && input[s.i + 1] == input[s.i])
			{
				tokens[s.j++] = ft_strndup(&input[s.i], 2);
				s.i += 2;
			}
			else
			{
				tokens[s.j++] = ft_strndup(&input[s.i], 1);
				s.i++;
			}
		}
		else
		{
			// Regular token or quoted token - read everything until space or unquoted operator
			bool inside_quotes = false;
			char quote_char = 0;
			
			while (input[s.i] && (input[s.i] != ' ' || inside_quotes))
			{
				if (!inside_quotes && (input[s.i] == '|' || input[s.i] == '<' || input[s.i] == '>'))
					break;
					
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
				else
				{
					s.i++;
				}
			}
			save_token(tokens, &s, input, s.i, env);
		}
	}
	
	tokens[s.j] = NULL;
	return (tokens);
}
