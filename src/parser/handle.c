/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:38:07 by ebalana-          #+#    #+#             */
/*   Updated: 2025/05/29 15:42:09 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void handle_end(char **tokens, const char *input, t_token_state *s, t_env *env)
{
	if (input[s->i] == ' ' || input[s->i] == '\0')
	{
		save_token(tokens, s, input, s->i, env);
		while (input[s->i] == ' ')
			s->i++;
		s->start = s->i;
	}
}

void handle_redirection(char **tokens, const char *input, t_token_state *s, t_env *env)
{
	if (input[s->i] == '|' || input[s->i] == '<' || input[s->i] == '>')
	{
		save_token(tokens, s, input, s->i, env);
		if ((input[s->i] == '<' || input[s->i] == '>') && input[s->i + 1] == input[s->i])
		{
			tokens[s->j++] = ft_strndup(&input[s->i], 2);
			s->i++;
		}
		else
			tokens[s->j++] = ft_strndup(&input[s->i], 1);
		s->i++;
		while (input[s->i] == ' ')
			s->i++;
		s->start = s->i;
	}
}
