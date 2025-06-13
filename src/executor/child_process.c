/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:26:19 by mavellan          #+#    #+#             */
/*   Updated: 2025/06/13 15:23:58 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Redirige entrada/salida estándar para pipes.
 * Conecta stdin del proceso anterior y stdout al siguiente pipe.
*/
void	redirect_io(t_cmd *cmd, t_exec_data *exec_data)
{
	if (exec_data->prev_read != STDIN_FILENO)
	{
		dup2(exec_data->prev_read, STDIN_FILENO);
		close(exec_data->prev_read);
	}
	if (cmd->next != NULL)
	{
		dup2(exec_data->pipe_fds[1], STDOUT_FILENO);
		close(exec_data->pipe_fds[0]);
		close(exec_data->pipe_fds[1]);
	}
}

/*
 * Ejecuta builtin en proceso hijo si aplica.
 * Exit se maneja especialmente para no terminar el shell principal.
*/
void	execute_if_builtin(t_cmd *cmd, t_exec_data *exec_data)
{
	int	status;

	if (!is_builtin(cmd->args[0]))
		return ;
	status = execute_builtin(cmd->args, &(exec_data->env_list));
	exit(status);
}

/*
 * Verifica errores de ejecutabilidad del archivo.
 * Comprueba existencia, permisos y si es directorio.
*/
void	check_executable_errors(char *path, char **envp)
{
	struct stat	path_stat;

	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd("minishell: no such file or directory\n", 2);
		free(path);
		ft_free(envp);
		exit(127);
	}
	if (access(path, X_OK) != 0)
	{
		ft_putstr_fd("minishell: permission denied\n", 2);
		free(path);
		ft_free(envp);
		exit(126);
	}
	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free(path);
		ft_free(envp);
		exit(126);
	}
}

/*
 * Maneja comando no encontrado.
 * Muestra error y termina proceso hijo con código 127.
*/
void	execute_command(t_cmd *cmd, char **envp_array, char *full_path)
{
	check_executable_errors(full_path, envp_array);
	execve(full_path, cmd->args, envp_array);
	if (errno == ENOEXEC)
		handle_execve_sh_fallback(full_path, envp_array);
	ft_putstr_fd("minishell: execution error\n", 2);
	free(full_path);
	ft_free(envp_array);
	exit(127);
}

/*
 * Maneja fallback con /bin/sh cuando execve falla.
 * Intenta ejecutar como script de shell.
*/
void	setup_child_process(t_cmd *cmd, t_exec_data *exec_data)
{
	char	**envp_array;
	char	*full_path;

	redirect_io(cmd, exec_data);
	apply_redirections(cmd);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	execute_if_builtin(cmd, exec_data);
	envp_array = convert_env_to_envp(exec_data->env_list);
	full_path = get_full_command_path(cmd->args[0], exec_data->env_list);
	if (!full_path)
		handle_command_not_found(cmd, envp_array);
	execute_command(cmd, envp_array, full_path);
}
