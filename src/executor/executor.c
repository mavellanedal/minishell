/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:50:46 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/08 12:36:09 by mavellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	apply_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

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

void	execute_command(t_cmd *cmd, char **envp, int *pipe_fds)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		apply_redirections(cmd);
		if (pipe_fds != NULL)
		{
			dup2(pipe_fds[1], STDOUT_FILENO);
			close(pipe_fds[0]);
			close(pipe_fds[1]);
		}

		if (execve(cmd->args[0], cmd->args, envp) == -1)
		{
			perror("Error executing the command");
			exit(127);
		}
	}
}

void	create_pipes(t_cmd *cmd, int *pipe_fds)
{
	if (cmd->next != NULL)
	{
		if (pipe(pipe_fds) == -1)
		{
			perror("pipe");
			exit(1);
		}
	}
}

void	wait_for_processes(pid_t pid)
{
	int	status;
	int	exit_status;
	int	signal_num;

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

void	executor(t_cmd *cmd_list, t_env *env)
{
	t_cmd	*cmd;
	int		prev_read;
	int		pipe_fds[2];
	pid_t	pid;
	char	**envp;

	envp = env_to_envp(env);
	if (!envp)
	{
		perror("Error \n Filed to create envp");
		exit(1);
	}
	prev_read = -1;
	cmd = cmd_list;
	while (cmd)
	{
		if (cmd->next != NULL)
			create_pipes(cmd, pipe_fds);
		else
		{
			pipe_fds[0] = pipe_fds[1];
			pipe_fds[1] = -1;
		}
		pid = fork_and_execute_command(cmd, envp, prev_read, pipe_fds);
		if (prev_read != -1)
			close(prev_read);
		if (cmd->next != NULL)
		{
			close(pipe_fds[1]);
			prev_read = pipe_fds[0];
		}
		else
			prev_read = -1;
		wait_for_processes(pid);
		cmd = cmd->next;
	}
	ft_free(envp);
}
