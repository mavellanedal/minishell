/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:40:15 by mavellan          #+#    #+#             */
/*   Updated: 2025/06/13 14:50:44 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Ejecuta comandos procesando heredocs primero.
 * Maneja interrupciones y retorna código de salida apropiado.
*/
int	execute_with_heredocs(t_cmd *cmd_list, t_env **env_list)
{
	int	heredoc_result;
	int	status;

	heredoc_result = process_heredocs(cmd_list, *env_list);
	if (heredoc_result == 130)
	{
		printf("\n");
		cleanup_heredoc_fds(cmd_list);
		return (130);
	}
	else if (heredoc_result == 0)
	{
		status = executor(cmd_list, env_list);
		cleanup_heredoc_fds(cmd_list);
		return (status);
	}
	else
	{
		cleanup_heredoc_fds(cmd_list);
		return (heredoc_result);
	}
}

/*
 * Expande variables en todos los tokens del array.
 * Procesa $VAR, $? y maneja comillas en cada token.
*/
void	expand_all_tokens(char **tokens, int status, t_env *env_list)
{
	char	*expanded;
	int		i;

	i = 0;
	while (tokens[i])
	{
		expanded = process_token_properly(tokens[i], status, env_list);
		free(tokens[i]);
		tokens[i] = expanded;
		i++;
	}
}

/*
 * Procesa una línea de entrada completa.
 * Tokeniza, expande, parsea y ejecuta comandos.
*/
int	handle_input_line(char *line, int last_status, t_env **env_list)
{
	char	**tokens;
	t_cmd	*cmd_list;

	if (!*line)
		return (last_status);
	add_history(line);
	tokens = tokenize_input(line, last_status, *env_list);
	if (!tokens)
		return (last_status);
	expand_all_tokens(tokens, last_status, *env_list);
	cmd_list = parse_tokens_to_cmd_list(tokens, &last_status);
	if (cmd_list)
		last_status = execute_with_heredocs(cmd_list, env_list);
	free_cmd_list(cmd_list);
	free_tokens(tokens);
	return (last_status);
}

/*
 * Bucle principal del shell.
 * Lee entrada, procesa comandos y maneja EOF.
*/
void	shell_loop(t_env *env_list, int last_status)
{
	char	*line;

	while (1)
	{
		g_heredoc_interrupted = 0;
		line = readline("minishell$ ");
		if (g_heredoc_interrupted == 130)
		{
			last_status = 130;
			g_heredoc_interrupted = 0;
		}
		if (!line)
		{
			write(1, "exit\n", 5);
			free_env_list(env_list);
			break ;
		}
		last_status = handle_input_line(line, last_status, &env_list);
		free(line);
	}
}

/*
 * Función principal del programa.
 * Inicializa entorno, señales y ejecuta shell_loop.
*/
int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	int		last_status;

	(void)argc;
	(void)argv;
	last_status = 0;
	env_list = create_env_list(envp);
	update_shlvl(&env_list);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	shell_loop(env_list, last_status);
	return (0);
}
