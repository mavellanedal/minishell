/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:29:46 by mavellan          #+#    #+#             */
/*   Updated: 2025/06/02 15:43:51 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_builtin(t_cmd *cmd, t_env **env_list)
{
	int		status;
	char	*cmd_name;

	cmd_name = cmd->args[0];
	status = execute_builtin(cmd->args, env_list);
	if (ft_strcmp(cmd_name, "exit") == 0 && status != 1)
		exit(status);
	return (status);
}

int	handle_command(t_cmd *cmd, t_exec_data *exec_data, t_env **env_list)
{
	char	*first_arg;

	if (cmd->args)
		first_arg = cmd->args[0];
	else
		first_arg = NULL;
	if (is_builtin(first_arg) && !cmd->next && \
			exec_data->prev_read == STDIN_FILENO && !cmd->redirs)
	{
		return (handle_builtin(cmd, env_list));
	}
	else if ((!cmd->args || !cmd->args[0]) && cmd->redirs)
	{
		return (handle_redirection_only(cmd, exec_data));
	}
	else if (!cmd->args || !cmd->args[0])
	{
		ft_putstr_fd("minishell: command not found\n", STDERR_FILENO);
		return (127);
	}
	return (handle_full_command(cmd, exec_data));
}

void	handle_pipe_end(t_cmd *cmd, t_exec_data *exec_data)
{
	if (exec_data->prev_read != STDIN_FILENO)
		close(exec_data->prev_read);
	if (cmd->next)
	{
		close(exec_data->pipe_fds[1]);
		exec_data->prev_read = exec_data->pipe_fds[0];
	}
	else
		exec_data->prev_read = -1;
}

int	handle_redirection_only(t_cmd *cmd, t_exec_data *exec_data)
{
	pid_t	pid;
	int		status;

	setup_pipe(cmd, exec_data);
	exec_data->cmd = cmd;
	pid = fork_and_execute_command(cmd, exec_data);
	handle_pipe_end(cmd, exec_data);
	wait_and_get_status(pid, &status);
	return (status);
}

int	handle_full_command(t_cmd *cmd, t_exec_data *exec_data)
{
	pid_t	pid;
	int		status;

	setup_pipe(cmd, exec_data);
	exec_data->cmd = cmd;
	pid = fork_and_execute_command(cmd, exec_data);
	handle_pipe_end(cmd, exec_data);
	wait_and_get_status(pid, &status);
	return (status);
}
