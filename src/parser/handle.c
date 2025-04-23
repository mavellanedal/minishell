/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:38:07 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/23 19:35:54 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_end(char **tokens, const char *input, t_token_state *s)
{
	t_quote_state	q;

	q = get_quote_state(input, s->i);
	if ((input[s->i] == ' ' || input[s->i] == '\0') \
		&& !(q.in_single || q.in_double))
	{
		save_token(tokens, s, input, s->i);
		s->start = s->i + 1;
	}
}

void	handle_redirection(char **tokens, const char *input, t_token_state *s)
{
	t_quote_state	q;

	q = get_quote_state(input, s->i);
	if ((input[s->i] == '|' || input[s->i] == '<' || input[s->i] == '>') \
		&& !(q.in_single || q.in_double))
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

void	handle_quote(char c, bool *in_single, bool *in_double, bool *has_single)
{
	if (c == '\'' && !(*in_double))
	{
		*in_single = !(*in_single);
		*has_single = true;
	}
	else if (c == '\"' && !(*in_single))
	{
		*in_double = !(*in_double);
	}
}

void	handle_dollar(t_expand_state *s)
{
	if (s->str[*(s->i)] == '?')
	{
		s->j += sprintf(s->res + s->j, "%d", s->last_status);
		(*(s->i))++;
	}
	else if (ft_isalpha(s->str[*(s->i)]) || s->str[*(s->i)] == '_')
	{
		int start = *(s->i);
		while (ft_isalnum(s->str[*(s->i)]) || s->str[*(s->i)] == '_')
			(*(s->i))++;
		char *var = ft_substr(s->str, start, *(s->i) - start);
		char *val = getenv(var);
		free(var);
		if (val)
			s->j += sprintf(s->res + s->j, "%s", val);
	}
	else
	{
		s->res[s->j++] = '$';
	}
}
