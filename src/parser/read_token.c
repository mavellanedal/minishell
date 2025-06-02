/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:50:50 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/02 13:51:49 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	handle_quotes(const char *input, int *i, bool *inside_quotes, \
	char *quote_char)
{
	if ((input[*i] == '\'' || input[*i] == '\"') && !(*inside_quotes))
	{
		*inside_quotes = true;
		*quote_char = input[*i];
		(*i)++;
		return (true);
	}
	else if (*inside_quotes && input[*i] == *quote_char)
	{
		*inside_quotes = false;
		*quote_char = 0;
		(*i)++;
		return (true);
	}
	return (false);
}

bool	handle_operator(const char *input, int *i, int start, bool inside_quote)
{
	if (!inside_quote && (input[*i] == '|' || input[*i] == '<' || \
		input[*i] == '>'))
	{
		if (*i == start)
		{
			if ((input[*i] == '<' || input[*i] == '>') && \
				input[*i + 1] == input[*i])
				(*i) += 2;
			else
				(*i)++;
			return (true);
		}
		else
			return (true);
	}
	return (false);
}

void	read_token(const char *input, int *i, int *start)
{
	bool	inside_quotes;
	char	quote_char;

	inside_quotes = false;
	quote_char = 0;
	*start = *i;
	while (input[*i] && (input[*i] != ' ' || inside_quotes))
	{
		if (handle_quotes(input, i, &inside_quotes, &quote_char))
			continue ;
		if (handle_operator(input, i, *start, inside_quotes))
			break ;
		(*i)++;
	}
}

void	process_heredoc(const char *input, t_token_state *s, char **tokens)
{
	char	*literal_token;
	int		start;
	int		len;

	if (s->j > 0 && ft_strcmp(tokens[s->j - 1], "<<") == 0)
	{
		skip_spaces(input, &(s->i));
		if (!input[s->i])
			return ;
		start = s->i;
		while (input[s->i] && input[s->i] != ' ' && input[s->i] != '|' && \
				input[s->i] != '<' && input[s->i] != '>')
			s->i++;
		len = s->i - start;
		literal_token = malloc(len + 2);
		if (!literal_token)
			return ;
		literal_token[0] = '\1';
		strncpy(&literal_token[1], &input[start], len);
		literal_token[len + 1] = '\0';
		tokens[s->j++] = literal_token;
	}
}
