/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:16:14 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/02 14:03:33 by ebalana-         ###   ########.fr       */
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
		skip_spaces(input, &(s.i));
		if (!input[s.i])
			break ;
		read_token(input, &(s.i), &(s.start));
		save_token(tokens, &s, input, s.i);
		process_heredoc(input, &s, tokens);
	}
	tokens[s.j] = NULL;
	return (tokens);
}
