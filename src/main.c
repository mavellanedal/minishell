/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:40:15 by mavellan          #+#    #+#             */
/*   Updated: 2025/04/29 17:13:56 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int main(void)
// {
// 	char *line;

// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		if (!line)
// 			break;
// 		if (*line)
// 		{
// 			add_history(line);
// 			tokenize_input(line);
// 		}
// 		free(line);
// 	}
// 	return 0;
// }

int main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**tokens;
	int		last_status = 0;
	t_env	*env_list;

	env_list = create_env_list(envp);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break;
		if (*line)
		{
			add_history(line);
			tokens = tokenize_input(line, last_status);
			if (tokens)
			{
				// Expandir variables y eliminar comillas
				for (int i = 0; tokens[i]; i++)
				{
					char *expanded = remove_quotes_and_expand(tokens[i], last_status);
					free(tokens[i]);
					tokens[i] = expanded;
				}

				// 👇 Ejecutar builtins si corresponde
				if (execute_builtin(tokens, env_list) == -1)
				{
					// No es builtin → comando externo
					pid_t pid = fork();
					if (pid == 0)
					{
						execvp(tokens[0], tokens);
						perror("execvp");
						exit(127);
					}
					else
					{
						int status;
						waitpid(pid, &status, 0);
						last_status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
					}
				}
			}
			for (int i = 0; tokens && tokens[i]; i++)
				free(tokens[i]);
			free(tokens);
		}
		free(line);
	}
	return (0);
}
