/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:26:19 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/17 18:11:50 by mavellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	setup_child_process(t_cmd *cmd, t_exec_data *exec_data)
{
	char	**envp_array;
	char	*full_path;

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

	apply_redirections(cmd);

	if (is_builtin(cmd->args[0]))
	{
		int status = execute_builtin(cmd->args, &(exec_data->env_list));
		exit(status);
	}

	envp_array = convert_env_to_envp(exec_data->env_list);

	if (ft_strchr(cmd->args[0], '/'))
		full_path = strdup(cmd->args[0]);
	else
		full_path = find_command_path(cmd->args[0], exec_data->env_list);

	if (!full_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_free(envp_array);
		exit(127);
	}

	if (access(full_path, F_OK) != 0)
	{
		ft_putstr_fd("minishell: no such file or directory\n", 2);
		free(full_path);
		ft_free(envp_array);
		exit(127);
	}
	if (access(full_path, X_OK) != 0)
	{
		ft_putstr_fd("minishell: permission denied\n", 2);
		free(full_path);
		ft_free(envp_array);
		exit(126);
	}

	struct stat path_stat;
	if (stat(full_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(full_path, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free(full_path);
		ft_free(envp_array);
		exit(126);
	}
	execve(full_path, cmd->args, envp_array);
	ft_putstr_fd("minishell: execution error\n", 2);
	free(full_path);
	ft_free(envp_array);
	exit(127);
}



pid_t	fork_and_execute_command(t_cmd *cmd, t_exec_data *exec_data)
{
	pid_t	pid;

	// ft_printf("Dentro de fork_and_execute_command\n");
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
		setup_child_process(cmd, exec_data);
	return (pid);
}
