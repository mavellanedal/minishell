/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:40:15 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/02 13:41:07 by mavellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
			break ; //Ctrl+D
		if (*line)
		{
			add_history(line);
			tokens = tokenize_input(line, last_status);
			if (tokens)
			{
				//printf("-----------------------------------------\n");
				int i = 0;
				while (tokens[i])
				{
					//printf("Tokens[%d] = [%s]\n", i, tokens[i]);
					char *expanded = remove_quotes_and_expand(tokens[i], last_status);
					free(tokens[i]);
					tokens[i] = expanded;
					i++;
				}
				//printf("-----------------------------------------\n");
				// Si no es built-in, ejecutar como externo
				if (execute_builtin(tokens, env_list) == -1)
				{
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
