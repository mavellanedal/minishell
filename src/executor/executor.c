/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:50:46 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/15 08:52:43 by mavellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	apply_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	ft_printf("Dentro de apply_redirections\n");
	r = cmd->redirs;
	while (r)
	{
		fd = check_redir_type(r);
		if (fd > 0)
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

void	wait_for_processes(pid_t pid)
{
	int	status;
	int	exit_status;
	int	signal_num;


	ft_printf("Dentro de wait_for_processes\n");
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		printf("Process %d ended with statu: %d\n", pid, exit_status);
	}
	else if (WIFSIGNALED(status))
	{
		signal_num = WTERMSIG(status);
		printf("Process %d ended by signal: %d\n", pid, signal_num);
	}
}

void	executor(t_cmd *cmd_list, t_env *env_list)
{
	t_exec_data	exec_data;
	pid_t	pid;

	ft_printf("Dentro del executor\n");
	exec_data.env_list = env_list;
	exec_data.prev_read = STDIN_FILENO;
	exec_data.cmd = cmd_list;

	while (exec_data.cmd)
	{
		if (exec_data.cmd->next)
			pipe(exec_data.pipe_fds);
		else
		{
			exec_data.pipe_fds[0] = -1;
			exec_data.pipe_fds[1] = -1;
		}
		pid = fork_and_execute_command(exec_data.cmd, &exec_data);
		if (exec_data.prev_read != STDIN_FILENO)
			close(exec_data.prev_read);
		if (exec_data.cmd->next != NULL)
		{
			close(exec_data.pipe_fds[1]);
			exec_data.prev_read = exec_data.pipe_fds[0];
		}
		else
			exec_data.prev_read = -1;
		wait_for_processes(pid);
		exec_data.cmd = exec_data.cmd->next;
	}
	ft_free(exec_data.envp);
}
