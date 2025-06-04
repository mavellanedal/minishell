/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:16:14 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/04 13:38:12 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_token_state(t_token_state *s, int last_status, t_env *env)
{
	s->i = 0;
	s->j = 0;
	s->start = 0;
	s->last_status = last_status;
	s->env = env;
}

void	fill_token_array(const char *input, char **tokens, t_token_state *s)
{
	while (input[s->i])
	{
		skip_spaces(input, &s->i);
		if (!input[s->i])
			break ;
		read_token(input, &s->i, &s->start);
		save_token(tokens, s, input, s->i);
		process_heredoc(input, s, tokens);
	}
	tokens[s->j] = NULL;
}

int	validate_token_array(char **tokens)
{
	int	syntax_error;

	syntax_error = validate_syntax(tokens);
	if (syntax_error != 0)
	{
		free_tokens(tokens);
		return (syntax_error);
	}
	return (0);
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
	fill_token_array(input, tokens, &s);
	if (validate_token_array(tokens) != 0)
		return (NULL);
	return (tokens);
}
