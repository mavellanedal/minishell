/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:26:19 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/14 10:07:56 by mavellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	setup_child_process(t_cmd *cmd_list, t_exec_data *exec_data)
{
	ft_printf("Dentro de setup_child_process\n");
	char	**envp_array;

	if (exec_data->prev_read != STDIN_FILENO)
	{
		dup2(exec_data->prev_read, STDIN_FILENO);
		close(exec_data->prev_read);
	}
	if (cmd_list->next != NULL)
	{
		dup2(exec_data->pipe_fds[1], STDOUT_FILENO);
		close(exec_data->pipe_fds[0]);
		close(exec_data->pipe_fds[1]);
	}
	apply_redirections(cmd_list);
	envp_array = convert_env_to_envp(exec_data->env_list);
	if (!cmd_list->args || !cmd_list->args[0])
	{
		ft_putstr_fd("minishell: command not found\n", STDERR_FILENO);
		exit(127);
	}
	ft_printf("fuera de convert_env_to_envp\n");
	ft_printf("cmd_list->args: %p\n", cmd_list->args);
	ft_printf("cmd_list->args[0]: %s\n", cmd_list->args[0]);
	ft_printf("envp_array: %p\n", envp_array);
	if (execve(cmd_list->args[0], cmd_list->args, envp_array))
	{
		perror("execve");
		exit(127);
	}
	ft_printf("fuera de execve\n");
}

pid_t	fork_and_execute_command(t_cmd *cmd_list, t_exec_data *exec_data)
{
	pid_t	pid;

	ft_printf("Dentro de fork_and_execute_command\n");
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
		setup_child_process(cmd_list, exec_data);
	return (pid);
}
