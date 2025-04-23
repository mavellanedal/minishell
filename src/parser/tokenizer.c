/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:16:14 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/23 16:19:25 by ebalana-         ###   ########.fr       */
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

void	save_token(char **tokens, t_token_state *s, const char *input, int end)
{
	int	len;

	len = end - s->start;
	if (len > 0)
	{
		tokens[s->j] = strndup(&input[s->start], len);
		s->j++;
	}
}

void	handle_end(char **tokens, const char *input, t_token_state *s)
{
	t_quote_state	q;
	q = get_quote_state(input, s->i);
	if ((input[s->i] == ' ' || input[s->i] == '\0') && !(q.in_single || q.in_double))
	{
		save_token(tokens, s, input, s->i);
		s->start = s->i + 1;
	}
}

void	handle_redirection(char **tokens, const char *input, t_token_state *s)
{
	t_quote_state	q;
	q = get_quote_state(input, s->i);
	if ((input[s->i] == '|' || input[s->i] == '<' || input[s->i] == '>') && !(q.in_single || q.in_double))
	{
		if (input[s->i] == '<' || input[s->i] == '>')
		{
			save_token(tokens, s, input, s->i);
			if (input[s->i + 1] == input[s->i])
			{
				tokens[s->j++] = strndup(&input[s->i], 2);
				s->i++;
			}
			else
				tokens[s->j++] = strndup(&input[s->i], 1);
		}
		else
		{
			save_token(tokens, s, input, s->i);
			tokens[s->j++] = strndup(&input[s->i], 1);
		}
		s->start = s->i + 1;
	}
}

char	**tokenize_input(const char *input)
{
	char			**tokens;
	t_token_state	s;
	t_quote_state	q;

	q = get_quote_state(input, -1);
	if (q.in_single || q.in_double)
	{
		printf("minishell: error: unclosed quotes\n");
		return (NULL);
	}
	tokens = malloc(sizeof(char *) * 1024);
	if (!tokens)
		return (NULL);
	s.i = 0;
	s.j = 0;
	s.start = 0;
	while (input[s.i])
	{
		handle_end(tokens, input, &s);
		handle_redirection(tokens, input, &s);
		s.i++;
	}
	handle_end(tokens, input, &s);
	handle_redirection(tokens, input, &s);
	tokens[s.j] = NULL;
	return (tokens);
}

// char	**tokenize_input(const char *input)
// {
// 	char **tokens = malloc(sizeof(char *) * 1024);
// 	int i = 0, j = 0, start = 0;
// 	int len = strlen(input);

// 	while (i <= len)
// 	{
// 		if ((input[i] == ' ' || input[i] == '\0') && !is_quotes(input, i))
// 		{
// 			if (i > start)
// 			{
// 				int tok_len = i - start;
// 				tokens[j] = strndup(&input[start], tok_len);
// 				j++;
// 			}
// 			start = i + 1;
// 		}
// 		else if (input[i] == '|' || input[i] == '>' || input[i] == '<')
// 		{
// 			if (i > start)
// 			{
// 				int tok_len = i - start;
// 				tokens[j] = strndup(&input[start], tok_len);
// 				j++;
// 			}
// 			tokens[j] = strndup(&input[i], 1); // Pipe o redirección
// 			j++;
// 			start = i + 1;
// 		}
// 		i++;
// 	}
// 	tokens[j] = NULL;
// 	return tokens;
// }