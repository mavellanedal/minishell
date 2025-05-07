/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:40:15 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/06 18:47:34 by ebalana-         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**tokens;
	int		last_status;
	t_env	*env_list;

	last_status = 0;
	env_list = create_env_list(envp);    
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break; // Ctrl+D
		if (*line)
		{
			add_history(line);
			tokens = tokenize_input(line, last_status);
			if (tokens)
			{
				printf("-----------------------------------------\n");
				int i = 0;
				while (tokens[i])
				{
					printf("Tokens[%d] = [%s]\n", i, tokens[i]);
					char *expanded = remove_quotes_and_expand(tokens[i], last_status);
					free(tokens[i]);
					tokens[i] = expanded;
					i++;
				}
				printf("-----------------------------------------\n");
				
				// Si no es built-in, ejecutar como externo
				if (execute_builtin(tokens, &env_list) == -1)
				{
					char **env_array = env_list_to_array(env_list);
					pid_t pid = fork();
					if (pid == 0)
					{
						execve(tokens[0], tokens, env_array);
						perror("execve");
						free_env_array(env_array);
						exit(127);
					}
					else
					{
						int status;
						waitpid(pid, &status, 0);
						last_status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
					}
					free_env_array(env_array);
				}
			}
			int j = 0;
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
