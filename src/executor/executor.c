/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:50:46 by mavellan          #+#    #+#             */
/*   Updated: 2025/06/10 17:49:06 by ebalana-         ###   ########.fr       */
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

/*----------------------------------------------------------------------------------*/

/*
 * Espera a que terminen todos los procesos del pipeline.
 * El último comando establece el código de salida final.
*/
int	wait_for_all_processes(pid_t *pids, int cmd_count)
{
    int	i;
    int	status;
    int	last_status;

    last_status = 0;
    for (i = 0; i < cmd_count; i++)
    {
        wait_and_get_status(pids[i], &status);
        if (i == cmd_count - 1)  // El último comando establece el exit status
            last_status = status;
    }
    return (last_status);
}

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
 * Ejecuta un pipeline de comandos concurrentemente.
 * Crea todos los procesos primero, luego espera a todos.
*/
int	execute_pipeline(t_cmd *cmd_list, t_env **env_list)
{
    t_exec_data	exec_data;
    pid_t		*pids;
    int			cmd_count;
    int			last_status;
    t_cmd		*cmd;
    int			i;

    cmd_count = count_commands(cmd_list);
    pids = malloc(sizeof(pid_t) * cmd_count);
    if (!pids)
        return (1);
    
    exec_data.env_list = *env_list;
    exec_data.prev_read = STDIN_FILENO;
    
    // Fork todos los procesos
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
    
    // Esperar a todos los procesos
    last_status = wait_for_all_processes(pids, cmd_count);
    free(pids);
    return (last_status);
}

/*
 * Maneja la ejecución de un comando único sin pipes.
 * Usa la lógica original para comandos individuales.
*/
int	handle_single_command(t_cmd *cmd, t_env **env_list)
{
    t_exec_data	exec_data;

    exec_data.env_list = *env_list;
    exec_data.prev_read = STDIN_FILENO;
    exec_data.pipe_fds[0] = -1;
    exec_data.pipe_fds[1] = -1;

    return (handle_command(cmd, &exec_data, env_list));
}

/*---------------------------------------------------------------*/

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

	// Si es un solo comando sin pipes
	if (!cmd_list->next)
		return (handle_single_command(cmd_list, env_list));

	// Si es un pipeline, ejecutar concurrentemente
	return (execute_pipeline(cmd_list, env_list));
}