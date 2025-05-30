/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:29:28 by ebalana-          #+#    #+#             */
/*   Updated: 2025/05/29 13:00:08 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*process_token_properly(const char *token, int last_status, t_env *env)
{
	char	*result;
	int		i = 0;
	int		j = 0;
	bool	in_single = false;
	bool	in_double = false;
	bool	escaped = false;
	bool	had_quotes = false;

	result = malloc(4096);
	if (!result)
		return (NULL);

	// Check if token starts with quotes
	if (token[0] == '\'' || token[0] == '\"')
		had_quotes = true;

	while (token[i])
	{
		if (escaped)
		{
			if (in_double && (token[i] == '$' || token[i] == '\"' || token[i] == '\\' || token[i] == '\n'))
				result[j++] = token[i];
			else if (!in_single && !in_double)
				result[j++] = token[i];
			else
			{
				result[j++] = '\\';
				result[j++] = token[i];
			}
			escaped = false;
			i++;
		}
		else if (token[i] == '\\' && !in_single)
		{
			escaped = true;
			i++;
		}
		else if (token[i] == '\'' && !in_double)
		{
			in_single = !in_single;
			i++;
		}
		else if (token[i] == '\"' && !in_single)
		{
			in_double = !in_double;
			i++;
		}
		else if (token[i] == '$' && !in_single)
		{
			i++;
			j += expand_variable_here(token, &i, result + j, last_status, env);
		}
		else
		{
			result[j++] = token[i++];
		}
	}
	
	// Mark special chars that came from quotes as literals
	if (had_quotes && j == 1 && (result[0] == '<' || result[0] == '>' || result[0] == '|'))
	{
		result[j+1] = result[0];
		result[0] = '\1';
		result[j+2] = '\0';
		return (result);
	}
	
	result[j] = '\0';
	return (result);
}

int	expand_variable_here(const char *str, int *i, char *result, int last_status, t_env *env)
{
	char	*var_name;
	char	*var_value;
	int		start;
	int		len = 0;

	if (str[*i] == '?')
	{
		len = sprintf(result, "%d", last_status);
		(*i)++;
	}
	else if (ft_isalpha(str[*i]) || str[*i] == '_')
	{
		start = *i;
		while (ft_isalnum(str[*i]) || str[*i] == '_')
			(*i)++;
		
		var_name = ft_substr(str, start, *i - start);
		var_value = get_env_value(env, var_name);
		
		if (var_value)
			len = sprintf(result, "%s", var_value);
		
		free(var_name);
	}
	else
	{
		result[0] = '$';
		len = 1;
	}
	
	return (len);
}
