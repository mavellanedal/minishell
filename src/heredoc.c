/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:15:33 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/03 13:18:19 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_heredoc_interrupted = 0;

int	run_heredoc_parent(pid_t pid, int *fd, int pipefd[2])
{
	int	status;

	signal(SIGINT, SIG_IGN);
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipefd[0]);
		sigint_handler(SIGINT);
		return (130);
	}
	if (WEXITSTATUS(status) == 130)
		return (close(pipefd[0]), 130);
	*fd = pipefd[0];
	return (0);
}

void	run_heredoc_child(char *delimiter, int pipefd[2])
{
	char	*line;

	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	close(pipefd[0]);
	while (!g_heredoc_interrupted)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = heredoc_readline();
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(pipefd[1]);
	exit(0);
}

int	handle_heredoc(char *delimiter, int *fd)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (close(pipefd[0]), close(pipefd[1]), -1);
	if (pid == 0)
		run_heredoc_child(delimiter, pipefd);
	return (run_heredoc_parent(pid, fd, pipefd));
}

int	process_cmd_heredocs(t_redir *redir)
{
	int	fd;
	int	result;

	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
		{
			result = handle_heredoc(redir->file, &fd);
			if (result == 130)
			{
				signal(SIGINT, sigint_handler);
				signal(SIGQUIT, SIG_IGN);
				return (130);
			}
			if (result != 0)
				return (result);
			redir->heredoc_fd = fd;
		}
		redir = redir->next;
	}
	return (0);
}

int	process_all_heredocs(t_cmd *cmd_list)
{
	int	result;

	g_heredoc_interrupted = 0;
	while (cmd_list)
	{
		result = process_cmd_heredocs(cmd_list->redirs);
		if (result != 0)
			return (result);
		cmd_list = cmd_list->next;
	}
	return (0);
}
