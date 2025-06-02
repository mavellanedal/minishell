/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:29:28 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/02 13:01:19 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Manejar $?
void	handle_exit_status(t_expand_params *params)
{
	char	*status_str;

	status_str = ft_itoa(params->last_status);
	if (!status_str)
		return ;
	ft_strcpy(params->result, status_str);
	params->len = ft_strlen(status_str);
	free(status_str);
	(*params->i)++;
}

// Manejar $VAR
void	handle_named_variable(t_expand_params *params)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = *(params->i);
	while (ft_isalnum(params->str[*(params->i)]) || \
		params->str[*(params->i)] == '_')
		(*params->i)++;
	var_name = ft_substr(params->str, start, *(params->i) - start);
	if (!var_name)
		return ;
	var_value = get_env_value(params->env, var_name);
	if (var_value)
	{
		ft_strcpy(params->result, var_value);
		params->len = ft_strlen(var_value);
	}
	free(var_name);
}

int	expand_variable_here(t_expand_params *params)
{
	params->len = 0;
	if (params->str[*(params->i)] == '?')
		handle_exit_status(params);
	else if (ft_isalpha(params->str[*(params->i)]) || \
		params->str[*(params->i)] == '_')
		handle_named_variable(params);
	else
	{
		params->result[0] = '$';
		params->len = 1;
	}
	return (params->len);
}
