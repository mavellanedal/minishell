/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:50:46 by mavellan          #+#    #+#             */
/*   Updated: 2025/04/24 13:34:30 by mavellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_infile(char *filename)
{
	int	fd = open(filename, O_RDONLY);
	if (fd < 0)
		perror("open infile");
	return (fd);
}

int	open_outfile(char *filename, int append)
{
	int	fd;

	if (append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		perror("open outfile");
	return (fd);
}

static void child_process(t_data *data, t_cmd *cmd, int i, int pipefd[2], int prev_fd)
{
	if (cmd->infile)
		dup2(open_infile(cmd->infile), STDIN_FILENO);
	else if (i != 0)
		dup2(prev_fd, STDIN_FILENO);

	if (cmd->outfile)
		dup2(open_outfile(cmd->outfile, cmd->append), STDOUT_FILENO);
	else if (i != data->num_cmds - 1)
		dup2(pipefd[1], STDOUT_FILENO);

	close(pipefd[0]);
	if (prev_fd != -1)
		close(prev_fd);

	execvp(cmd->tokens[0], cmd->tokens);
	perror("execvp");
	exit(127);
}

void execute(t_data *data)
{
	int pipefd[2];
	int prev_fd = -1;
	pid_t pid;
	int i;

	i = 0;
	while (i < data->num_cmds)
	{
		if (i < data->num_cmds - 1)
			pipe(pipefd);

		pid = fork();
		if (pid == 0)
		{
			if (i < data->num_cmds - 1)
				close(pipefd[0]);
			child_process(data, &data->cmds[i], i, pipefd, prev_fd);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (i < data->num_cmds - 1)
			{
				close(pipefd[1]);
				prev_fd = pipefd[0];
			}
		}
		i++;
	}
	while (wait(NULL) > 0)
		;
}
