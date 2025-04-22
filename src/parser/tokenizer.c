/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:16:14 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/22 18:38:11 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_quotes(const char *str, int i)
{
	bool	in_single;
	bool	in_double;
	int		j;

	in_single = false;
	in_double = false;
	j = 0;
	while (j < i)
	{
		if (str[j] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[j] == '\"' && !in_single)
			in_double = !in_double;
		j++;
	}
	return (in_single || in_double);
}

void	save_token(char **tokens, t_token_state *s, const char *input, int end)
{
	int	len;

	len = end - s->start;
	if (len > 0)
	{
		tokens[s->j] = ft_strndup(&input[s->start], len);
		s->j++;
	}
}

void	handle_end(char **tokens, const char *input, t_token_state *s)
{
	if ((input[s->i] == ' ' || input[s->i] == '\0') && !is_quotes(input, s->i))
	{
		save_token(tokens, s, input, s->i);
		s->start = s->i + 1;
	}
}

void	handle_redirection(char **tokens, const char *input, t_token_state *s)
{
	if ((input[s->i] == '|' || input[s->i] == '<' || input[s->i] == '>') \
	&& !is_quotes(input, s->i))
	{
		if (input[s->i] == '<' || input[s->i] == '>')
		{
			if (input[s->i + 1] == input[s->i])
			{
				save_token(tokens, s, input, s->i);
				tokens[s->j] = ft_strndup(&input[s->i], 2);
				s->j++;
				s->i++;
			}
			else
			{
				save_token(tokens, s, input, s->i);
				tokens[s->j] = ft_strndup(&input[s->i], 1);
				s->j++;
			}
		}
		s->start = s->i + 1;
	}
}

char	**tokenize_input(const char *input)
{
	char			**tokens;
	t_token_state	s;

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