/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:15:33 by ebalana-          #+#    #+#             */
/*   Updated: 2025/05/31 08:32:57 by mavellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

volatile sig_atomic_t g_heredoc_interrupted = 0;

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	exit(130);
}

// Función simple para leer línea por línea sin get_next_line
char	*read_line_from_stdin()
{
	char	buffer[1];
	char	*line;
	int		i;
	int		capacity;
	int		result;

	line = NULL;
	i = 0;
	capacity = 100;
	line = malloc(capacity);
	if (!line)
		return (NULL);
	while (read(STDIN_FILENO, buffer, 1) > 0)
	{
		result = handle_interrupt_or_newline(buffer, line, i);
		if (result == -1)
			return (NULL);
		if (result == 1)
			return (line);
		if (i >= capacity - 1)
		{
			line = expand_line_capacity(line, &capacity);
			if (!line)
				return (NULL);
		}
		line[i] = buffer[0];
		i++;
	}
	return (finalize_line(line, i));
}

int	handle_heredoc(char *delimiter, int *fd)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	if (pid == 0)
		child_heredoc_process(pipefd, delimiter);
	return (parent_heredoc_process(pipefd, fd, pid, &status));
}

int	process_all_heredocs(t_cmd *cmd_list)
{
	t_cmd *cmd = cmd_list;
	t_redir *redir;
	int fd;
	int result;

	g_heredoc_interrupted = 0;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				result = handle_heredoc(redir->file, &fd);
				if (result == 130)
				{
					signal(SIGINT, sigint_handler);
					signal(SIGQUIT, SIG_IGN);
					return 130;
				}
				if (result != 0)
					return result;
				redir->heredoc_fd = fd;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return 0;
}
