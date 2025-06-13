/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:20:30 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/13 15:01:20 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Cuenta el número de comandos en la lista.
 * Usado para saber cuántos procesos crear en el pipeline.
*/
int	count_commands(t_cmd *cmd_list)
{
	int		count;
	t_cmd	*cmd;

	count = 0;
	cmd = cmd_list;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

/*
 * Espera a que terminen todos los procesos del pipeline.
 * El último comando establece el código de salida final.
*/
int	wait_for_all_processes(pid_t *pids, int cmd_count)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 0;
	while (i < cmd_count)
	{
		wait_and_get_status(pids[i], &status);
		if (i == cmd_count - 1)
			last_status = status;
		i++;
	}
	return (last_status);
}

/*
 * Prepara y ejecuta todos los procesos del pipeline.
 * Retorna array de PIDs de los procesos creados.
*/
pid_t	*fork_all_processes(t_cmd *cmd_list, t_env **env_list, int cmd_count)
{
	t_exec_data	exec_data;
	pid_t		*pids;
	t_cmd		*cmd;
	int			i;

	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		return (NULL);
	exec_data.env_list = *env_list;
	exec_data.prev_read = STDIN_FILENO;
	cmd = cmd_list;
	i = 0;
	while (cmd)
	{
		setup_pipe(cmd, &exec_data);
		exec_data.cmd = cmd;
		pids[i] = fork_and_execute_command(cmd, &exec_data);
		handle_pipe_end(cmd, &exec_data);
		cmd = cmd->next;
		i++;
	}
	return (pids);
}

/*
 * Ejecuta un pipeline de comandos concurrentemente.
 * Función principal simplificada.
*/
int	execute_pipeline(t_cmd *cmd_list, t_env **env_list)
{
	pid_t	*pids;
	int		cmd_count;
	int		last_status;

	cmd_count = count_commands(cmd_list);
	pids = fork_all_processes(cmd_list, env_list, cmd_count);
	if (!pids)
	{
		cleanup_heredoc_fds(cmd_list);
		return (1);
	}
	last_status = wait_for_all_processes(pids, cmd_count);
	cleanup_heredoc_fds(cmd_list);
	free(pids);
	return (last_status);
}

/*
 * Maneja la ejecución de un comando único sin pipes.
 * Usa la lógica original para comandos individuales.
*/
int	handle_no_pipe(t_cmd *cmd, t_env **env_list)
{
	t_exec_data	exec_data;

	exec_data.env_list = *env_list;
	exec_data.prev_read = STDIN_FILENO;
	exec_data.pipe_fds[0] = -1;
	exec_data.pipe_fds[1] = -1;
	return (handle_command(cmd, &exec_data, env_list));
}
