/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:50:46 by mavellan          #+#    #+#             */
/*   Updated: 2025/06/11 18:25:36 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Espera a que termine un proceso hijo y obtiene su estado de salida.
 * Maneja señales SIGINT y SIGQUIT, restaura handlers.
 * Ctrl +C y Ctrl +\ se manejan para mostrar mensajes adecuados.
*/
void	wait_and_get_status(pid_t pid, int *last_status)
{
	int	status;
	int	sig;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (sig == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
		*last_status = 128 + sig;
	}
	else if (WIFEXITED(status))
		*last_status = WEXITSTATUS(status);
	else
		*last_status = 1;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

/*
 * Configura pipes para comunicación entre comandos.
 * Crea pipe si hay comando siguiente, sino inicializa a -1.
*/
void	setup_pipe(t_cmd *cmd, t_exec_data *exec_data)
{
	if (cmd->next)
		pipe(exec_data->pipe_fds);
	else
	{
		exec_data->pipe_fds[0] = -1;
		exec_data->pipe_fds[1] = -1;
	}
}

/*
 * Verifica sintaxis de pipes en la lista de comandos.
 * Detecta comandos vacíos entre pipes.
*/
int	check_pipe_syntax(t_cmd *cmd)
{
	while (cmd)
	{
		if ((!cmd->args || !cmd->args[0]) && !cmd->redirs)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", \
				STDERR_FILENO);
			return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}

/*
 * Función principal del executor.
 * Ejecuta secuencialmente todos los comandos de la lista.
*/
int	executor(t_cmd *cmd_list, t_env **env_list)
{
	t_exec_data	exec_data;
	t_cmd		*tmp;
	int			last_status;

	exec_data.env_list = *env_list;
	exec_data.prev_read = STDIN_FILENO;
	tmp = cmd_list;
	last_status = 0;
	if (check_pipe_syntax(tmp))
		return (2);
	if (!cmd_list->next)
		return (handle_no_pipe(cmd_list, env_list));
	return (execute_pipeline(cmd_list, env_list));
}
