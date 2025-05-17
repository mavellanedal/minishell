/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:38:07 by ebalana-          #+#    #+#             */
/*   Updated: 2025/05/15 16:40:17 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_end(char **tokens, const char *input, t_token_state *s, t_env *env)
{
	t_quote_state	q;

	q = get_quote_state(input, s->i);
	if ((input[s->i] == ' ' || input[s->i] == '\0') \
		&& !(q.in_single || q.in_double))
	{
		save_token(tokens, s, input, s->i, env);
		s->start = s->i + 1;
	}
}

void	handle_redirection(char **tokens, const char *input, t_token_state *s, t_env *env)
{
	t_quote_state	q;

	q = get_quote_state(input, s->i);
	if ((input[s->i] == '|' || input[s->i] == '<' || input[s->i] == '>') \
		&& !(q.in_single || q.in_double))
	{
		if (input[s->i] == '<' || input[s->i] == '>')
		{
			save_token(tokens, s, input, s->i, env);
			if (input[s->i + 1] == input[s->i])
			{
				tokens[s->j++] = ft_strndup(&input[s->i], 2);
				s->i++;
			}
			else
				tokens[s->j++] = ft_strndup(&input[s->i], 1);
		}
		else
		{
			save_token(tokens, s, input, s->i, env);
			tokens[s->j++] = ft_strndup(&input[s->i], 1);
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
	int		start;
	char	*var;
	char	*val;

	if (s->str[*(s->i)] == '?')
	{
		s->j += sprintf(s->res + s->j, "%d", s->last_status);
		(*(s->i))++;
	}
	else if (ft_isalpha(s->str[*(s->i)]) || s->str[*(s->i)] == '_')
	{
		start = *(s->i);
		while (ft_isalnum(s->str[*(s->i)]) || s->str[*(s->i)] == '_')
			(*(s->i))++;
		var = ft_substr(s->str, start, *(s->i) - start);
		val = get_env_value(s->env, var);
		if (val)
			s->j += sprintf(s->res + s->j, "%s", val);
		free(var);
	}
	else
	{
		s->res[s->j++] = '$';
	}
}

// void	handle_dollar(t_expand_state *s) //Sense sprintf(posar aquest per minishell)
// {
// 	int		start;
// 	char	*var;
// 	char	*val;
// 	char	*tmp;
// 	int		len;

// 	if (s->str[*(s->i)] == '?')
// 	{
// 		tmp = ft_itoa(s->last_status);
// 		len = ft_strlen(tmp);
// 		ft_memcpy(s->res + s->j, tmp, len);
// 		s->j += len;
// 		free(tmp);
// 		(*(s->i))++;
// 		return ;
// 	}
// 	if (!ft_isalpha(s->str[*(s->i)]) && s->str[*(s->i)] != '_')
// 		return (s->res[s->j++] = '$', (void)0);
// 	start = *(s->i);
// 	while (ft_isalnum(s->str[*(s->i)]) || s->str[*(s->i)] == '_')
// 		(*(s->i))++;
// 	var = ft_substr(s->str, start, *(s->i) - start);
// 	val = getenv(var);
// 	if (val)
// 	{
// 		len = ft_strlen(val);
// 		ft_memcpy(s->res + s->j, val, len);
// 		s->j += len;
// 	}
// 	free(var);
// }
