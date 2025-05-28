/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:29:28 by ebalana-          #+#    #+#             */
/*   Updated: 2025/05/28 14:14:01 by ebalana-         ###   ########.fr       */
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

	result = malloc(4096);
	if (!result)
		return (NULL);

	while (token[i])
	{
		if (escaped)
		{
			// Carácter escapado
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
			i++; // Skip quote
		}
		else if (token[i] == '\"' && !in_single)
		{
			in_double = !in_double;
			i++; // Skip quote
		}
		else if (token[i] == '$' && !in_single)
		{
			// Expandir variable
			i++;
			j += expand_variable_here(token, &i, result + j, last_status, env);
		}
		else
		{
			result[j++] = token[i++];
		}
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

/* ----------------------------------------------------------------------------*/

// char	*strip_quotes(const char *token, bool *has_single)
// {
// 	char	*temp;
// 	int		i;
// 	int		j;
// 	bool	in_single;
// 	bool	in_double;

// 	temp = malloc(4096);
// 	i = 0;
// 	j = 0;
// 	in_single = false;
// 	in_double = false;
// 	*has_single = false;
// 	while (token[i])
// 	{
// 		if ((token[i] == '\'' && !in_double) || \
// 			(token[i] == '\"' && !in_single))
// 			handle_quote(token[i++], &in_single, &in_double, has_single);
// 		else
// 			temp[j++] = token[i++];
// 	}
// 	temp[j] = '\0';
// 	return (temp);
// }

// char	*remove_quotes_and_expand(const char *token, int last_status, t_env *env)
// {
// 	char	*temp;
// 	char	*expanded;
// 	bool	has_single;

// 	temp = strip_quotes(token, &has_single);
// 	if (!has_single)
// 	{
// 		expanded = expand_variables(temp, last_status, env);
// 		free(temp);
// 		return (expanded);
// 	}
// 	return (temp);
// }

int	expand_named_variable(const char *str, int i, char *result, int j, t_env *env)
{
	int		start;
	int		len;
	char	*var_name;
	char	*value;

	start = i;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	len = i - start;
	var_name = ft_substr(str, start, len);
	value = get_env_value(env, var_name);
	free(var_name);
	if (value)
		j += sprintf(result + j, "%s", value);
	return (j);
}

// void	process_expansion_loop(t_expand_state *s)
// {
// 	int	i;
// 	int	j;

// 	i = *(s->i);
// 	j = s->j;
// 	while (s->str[i])
// 	{
// 		if (s->str[i] == '$')
// 		{
// 			i++;
// 			*(s->i) = i;
// 			handle_dollar(s);
// 			j = s->j;
// 			i = *(s->i);
// 		}
// 		else
// 			s->res[j++] = s->str[i++];
// 	}
// 	s->res[j] = '\0';
// }

// char	*expand_variables(const char *str, int last_status, t_env *env)
// {
// 	char			*res;
// 	int				i;
// 	int				j;
// 	t_expand_state	s;

// 	res = malloc(4096);
// 	if (!res)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	s.str = str;
// 	s.i = &i;
// 	s.res = res;
// 	s.j = j;
// 	s.last_status = last_status;
// 	s.env = env;
// 	process_expansion_loop(&s);
// 	return (res);
// }

/* ----------------------------------------------------------------------------*/

// char	*remove_quotes_and_expand(const char *token, int last_status)
// {
// 	char	*temp = malloc(4096);
// 	int		i = 0, j = 0;
// 	bool	in_single = false, in_double = false;
// 	bool	has_single_quotes = false;

// 	while (token[i])
// 	{
// 		if (token[i] == '\'' && !in_double)
// 		{
// 			in_single = !in_single;
// 			has_single_quotes = true;
// 			i++;
// 			continue;
// 		}
// 		if (token[i] == '\"' && !in_single)
// 		{
// 			in_double = !in_double;
// 			i++;
// 			continue;
// 		}
// 		temp[j++] = token[i++];
// 	}
// 	temp[j] = '\0';

// 	if (!has_single_quotes)
// 	{
// 		char *expanded = expand_variables(temp, last_status);
// 		free(temp);
// 		return expanded;
// 	}
// 	return temp;
// }

// char *expand_variables(const char *str, int last_status)
// {
// 	char *result;
// 	int i;
// 	int j;

// 	result = malloc(4096);
// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			i++;
// 			if (str[i] == '?')
// 			{
// 				j += sprintf(result + j, "%d", last_status);
// 				i++;
// 			}
// 			else if (ft_isalpha(str[i]) || str[i] == '_')
// 			{
// 				int start = i;
// 				while (ft_isalnum(str[i]) || str[i] == '_')
// 					i++;
// 				char *var_name = ft_substr(str, start, i - start);
// 				char *value = getenv(var_name);
// 				free(var_name);
// 				if (value)
// 					j += sprintf(result + j, "%s", value);
// 			}
// 			else
// 				result[j++] = '$';
// 		}
// 		else
// 			result[j++] = str[i++];
// 	}
// 	result[j] = '\0';
// 	return (result);
// }
