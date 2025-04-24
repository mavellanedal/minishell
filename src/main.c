/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:40:15 by mavellan          #+#    #+#             */
/*   Updated: 2025/04/24 13:46:29 by mavellan         ###   ########.fr       */
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

// int	main(void)
// {
// 	char	*line;
// 	char	**tokens;
// 	int		i;

// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		if (!line)
// 			break ;
// 		if (*line)
// 		{
// 			add_history(line);
// 			tokens = tokenize_input(line);
// 			if (tokens)
// 			{
// 				i = 0;
// 				while (tokens[i])
// 				{
// 					printf("Token[%d]: %s\n", i, tokens[i]);
// 					free(tokens[i]);
// 					i++;
// 				}
// 				free(tokens);
// 			}
// 		}
// 		free(line);
// 	}
// 	return (0);
// }

int	main(int argc, char **argv, char *env[])
{
	char	*line;
	char	**tokens;
	int		last_status = 0;
	t_env	env_struct;

	(void)argc;
	(void)argv;
	env_struct.env = env;
	while (1)
	{
		env_struct.paths = get_path_array(env_struct.env);
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			tokens = tokenize_input(line, last_status);
			if (tokens)
			{
				pid_t pid = fork();
				if (pid == 0)
				{
					for (int i = 0; tokens[i]; i++)
					{
						char *expanded = remove_quotes_and_expand(tokens[i], last_status);
						free(tokens[i]);
						tokens[i] = expanded;
					}
					execvp(tokens[0], tokens);
					exit(127);
				}
				else
				{
					int status;
					waitpid(pid, &status, 0);
					last_status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
				}
				for (int i = 0; tokens[i]; i++)
					printf("Token[%d]: %s\n", i, tokens[i]);

				for (int i = 0; tokens[i]; i++)
					free(tokens[i]);
				free(tokens);
			}
		}
		free(line);
	}
	return (0);
}
