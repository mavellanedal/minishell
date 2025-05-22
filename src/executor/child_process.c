/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:26:19 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/22 13:19:08 by mavellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	execute_if_builtin(t_cmd *cmd, t_exec_data *exec_data)
{
	int	status;

	if (is_builtin(cmd->args[0]))
	{
		status = execute_builtin(cmd->args, &(exec_data->env_list));
		exit(status);
	}
}

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

void	setup_child_process(t_cmd *cmd, t_exec_data *exec_data)
{
	char	**envp_array;
	char	*full_path;

	redirect_io(cmd, exec_data);
	apply_redirections(cmd);
	execute_if_builtin(cmd, exec_data);
	envp_array = convert_env_to_envp(exec_data->env_list);
	full_path = get_full_command_path(cmd->args[0], exec_data->env_list);
	if (!full_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_free(envp_array);
		exit(127);
	}
	check_executable_errors(full_path, envp_array);
	execve(full_path, cmd->args, envp_array);
	ft_putstr_fd("minishell: execution error\n", 2);
	free(full_path);
	ft_free(envp_array);
	exit(127);
}

pid_t	fork_and_execute_command(t_cmd *cmd, t_exec_data *exec_data)
{
	pid_t	pid;

	// Ignorar señales en el padre antes del fork
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		// Restaurar señales a comportamiento por defecto en el hijo
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		setup_child_process(cmd, exec_data);
	}
	return (pid);
}
