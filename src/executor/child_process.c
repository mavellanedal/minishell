/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:26:19 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/15 13:26:46 by mavellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	setup_child_process(t_cmd *cmd, t_exec_data *exec_data)
{
	char	**envp_array;

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
	envp_array = convert_env_to_envp(exec_data->env_list);

	char *full_path;

	if (strchr(cmd->args[0], '/'))
		full_path = strdup(cmd->args[0]);
	else
		full_path = find_command_path(cmd->args[0], exec_data->env_list);

	if (!full_path)
	{
		perror("command not found");
		ft_free(envp_array);
		exit(127);
	}

	execve(full_path, cmd->args, envp_array);
	perror("execve");
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
