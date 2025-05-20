/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:40:15 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/20 16:36:18 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Función actualizada para convertir la lista de env a un array de strings para execve
 * Solo incluye variables que tienen has_value = 1
*/
char	**env_list_to_array(t_env *env_list)
{
	int		count;
	int		len;
	t_env	*temp;
	char	**env_array;

	count = 0;
	temp = env_list;
	while (temp)
	{
		if (temp->has_value) // Solo contamos si has_value = 1
			count++;
		temp = temp->next;
	}
	// Asignar memoria para el array
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	// Copiar variables al array
	temp = env_list;
	count = 0;
	while (temp)
	{
		if (temp->has_value) // Solo añadimos si has_value = 1
		{
			len = ft_strlen(temp->key) + ft_strlen(temp->value) + 2; // +2 para '=' y '\0'
			env_array[count] = malloc(len);
			if (env_array[count])
			{
				snprintf(env_array[count], len, "%s=%s", temp->key, temp->value);
				count++;
			}
		}
		temp = temp->next;
	}
	env_array[count] = NULL;
	return (env_array);
}

/*
	Liberar memoria del array de entorno
*/
void	free_env_array(char **env_array)
{
	int i;

	i = 0;
	if (!env_array)
		return;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

/*
 * Actualizamos shlvl
*/
void	update_shlvl(t_env **env_list)
{
	t_env	*new_node;
	t_env	*current;
	char	*shlvl_value;
	int		new_level;

	current = *env_list;
	shlvl_value = NULL;
	new_level = 1;
	while (current)
	{
		if (ft_strcmp(current->key, "SHLVL") == 0)
		{
			if (current->value && *(current->value))
				new_level = ft_atoi(current->value) + 1;
			free(current->value);
			current->value = ft_itoa(new_level);
			current->has_value = 1;
			return ;
		}
		current = current->next;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = ft_strdup("SHLVL");
	new_node->value = ft_strdup("1");
	new_node->has_value = 1;
	new_node->next = *env_list;
	*env_list = new_node;
}

int main(int argc, char **argv, char **envp)
{
	char    *line;
	char	*expanded;
	char    **tokens;
	char	**env_array;
	int     last_status;
	t_env   *env_list;
	t_cmd	*cmd_list;
	int		j;
	int		i;
	pid_t	pid;

	last_status = 0;
	env_list = create_env_list(envp);
	update_shlvl(&env_list);

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break; // Ctrl+D
		if (*line)
		{
			add_history(line);
			tokens = tokenize_input(line, last_status, env_list);
			if (tokens)
			{
				//printf("-----------------------------------------\n");
				i = 0;
				while (tokens[i])
				{
					//printf("Tokens[%d] = [%s]\n", i, tokens[i]);
					expanded = remove_quotes_and_expand(tokens[i], last_status, env_list);
					free(tokens[i]);
					tokens[i] = expanded;
					i++;
				}
				//printf("-----------------------------------------\n");
				cmd_list = parse_tokens_to_cmd_list(tokens);
				if (cmd_list)
				{
					last_status = executor(cmd_list, &env_list, tokens);
					free_cmd_list(cmd_list);
				}
			}
			j = 0;
			while (tokens && tokens[j])
			{
				free(tokens[j]);
				j++;
			}
			free(tokens);
		}
		free(line);
	}
	return (0);
}
