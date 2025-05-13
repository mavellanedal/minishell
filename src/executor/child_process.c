/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:26:19 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/02 14:34:25 by mavellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	setup_child_process(t_cmd *cmd, int prev_read, \
int *pipe_fds, char **envp)
{
	if (prev_read != 1)
	{
		dup2(prev_read, STDIN_FILENO);
		close(prev_read);
	}
	if (cmd->next != NULL)
	{
		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
	}
	apply_redirections(cmd);
	if (execve(cmd->args[0], cmd->args, envp) == -1)
	{
		perror("Error executing the command");
		exit(127);
	}
}

pid_t	fork_and_execute_command(t_cmd *cmd, char **envp, \
int prev_read, int *pipe_fds)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
		setup_child_process(cmd, prev_read, pipe_fds, envp);
	return (pid);
}
