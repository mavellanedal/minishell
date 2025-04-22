/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:40:15 by mavellan          #+#    #+#             */
/*   Updated: 2025/04/22 18:12:45 by ebalana-         ###   ########.fr       */
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

int	main(void)
{
	char	*line;
	char	**tokens;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			tokens = tokenize_input(line);
			for (int i = 0; tokens[i]; i++)
				printf("Token[%d]: %s\n", i, tokens[i]);
			for (int i = 0; tokens[i]; i++)
				free(tokens[i]);
			free(tokens);
		}
		free(line);
	}
	return 0;
}
