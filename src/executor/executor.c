/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:50:46 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/20 17:26:13 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	apply_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	// ft_printf("Dentro de apply_redirections\n");
	r = cmd->redirs;
	while (r)
	{
		fd = check_redir_type(r);
		if (fd < 0)
		{
			perror("Error of redirection");
			exit(0);
		}
		if (r->type == REDIR_OUT || r->type == REDIR_APPEND)
			dup2(fd, STDOUT_FILENO);
		else if (r->type == REDIR_IN)
			dup2(fd, STDIN_FILENO);
		close(fd);
		r = r->next;
	}
}

int	executor(t_cmd *cmd_list, t_env **env_list, char **tokens)
	{
	t_exec_data	exec_data;
	pid_t		pid;
	t_cmd		*current_cmd;
	int			status;
	bool		must_fork;
	int			last_status;

	exec_data.env_list = *env_list;
	exec_data.prev_read = STDIN_FILENO;
	current_cmd = cmd_list;
	int i = 1;
	while (current_cmd)
	{
		must_fork = current_cmd->next != NULL || current_cmd->redirs != NULL;
		if (is_builtin(current_cmd->args[0]) && !must_fork)
			execute_builtin(current_cmd->args, env_list);
		else
		{
			// printf("llega executor\n");
			if (current_cmd->next)
				pipe(exec_data.pipe_fds);
			else
			{
				exec_data.pipe_fds[0] = -1;
				exec_data.pipe_fds[1] = -1;
			}
			exec_data.cmd = current_cmd;
			pid = fork_and_execute_command(current_cmd, &exec_data);
			if (exec_data.prev_read != STDIN_FILENO)
				close(exec_data.prev_read);
			if (current_cmd->next != NULL)
			{
				close(exec_data.pipe_fds[1]);
				exec_data.prev_read = exec_data.pipe_fds[0];
			}
			else
				exec_data.prev_read = -1;
			waitpid(pid, &status, 0);
		}
		// printf("Bucle %d %s\n", i, current_cmd->args[0]);
		current_cmd = current_cmd->next;
		i++;
	}
	if (WIFEXITED(status))
		last_status = WEXITSTATUS(status);
	else
		last_status = 1;
	return (last_status);
}

