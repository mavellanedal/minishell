/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:50:46 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/22 13:48:40 by mavellan         ###   ########.fr       */
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

int executor(t_cmd *cmd_list, t_env **env_list)
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
	t_cmd *tmp = cmd_list;
	while (tmp)
	{
		if (!tmp->args || !tmp->args[0])
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
			last_status = 258;
			return (last_status);
		}
		tmp = tmp->next;
	}
	while (current_cmd)
	{
		must_fork = current_cmd->next != NULL || current_cmd->redirs != NULL;
		if (current_cmd->args && current_cmd->args[0] &&
			is_builtin(current_cmd->args[0]) && !must_fork)
		{
			if (ft_strcmp(current_cmd->args[0], "exit") == 0)
			{
				if (!current_cmd->next && exec_data.prev_read == STDIN_FILENO)
				{
					last_status = execute_builtin(current_cmd->args, env_list);
					if (last_status != 1)
						exit(last_status);
				}
				else
					last_status = 0;
			}
			else
				last_status = execute_builtin(current_cmd->args, &exec_data.env_list);
		}
		else if (!current_cmd->args || !current_cmd->args[0])
		{
			ft_putstr_fd("minishell: command not found\n", STDERR_FILENO);
			last_status = 258;
			current_cmd = current_cmd->next;
			exit(last_status);
		}
		else
		{
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
			if (WIFSIGNALED(status))
			{
				int sig = WTERMSIG(status);
				if (sig == SIGINT)
					write(STDOUT_FILENO, "\n", 1);
				else if (sig == SIGQUIT)
					write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
				last_status = 128 + sig;
			}
			else if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else
				last_status = 1;

			signal(SIGINT, sigint_handler);
			signal(SIGQUIT, SIG_IGN);
		}
		current_cmd = current_cmd->next;
	}
	return (last_status);
}
