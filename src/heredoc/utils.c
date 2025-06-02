/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 08:26:04 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/31 08:33:53 by mavellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_line_capacity(char *line, int *capacity)
{
	char	*temp;
	int		new_capacity;

	new_capacity = (*capacity) * 2;
	temp = realloc(line, new_capacity);
	if (!temp)
	{
		free(line);
		return (NULL);
	}
	*capacity = new_capacity;
	return (temp);
}

int	handle_interrupt_or_newline(char *buffer, char *line, int i)
{
	if (g_heredoc_interrupted)
	{
		free(line);
		return (-1);
	}
	if (buffer[0] == '\n')
	{
		line[i] = '\0';
		return (1);
	}
	return (0);
}

char	*finalize_line(char *line, int i)
{
	if (i == 0)
	{
		free(line);
		return (NULL);
	}
	line[i] = '\0';
	return (line);
}

void	child_heredoc_process(int pipefd[2], char *delimiter)
{
	char	*line;
	int		match;

	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	close(pipefd[0]);
	while (!g_heredoc_interrupted)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = read_line_from_stdin(0);
		if (!line || g_heredoc_interrupted)
			break;
		match = ft_strcmp(line, delimiter);
		if (match == 0)
		{
			free(line);
			break;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	exit(0);
}

int	parent_heredoc_process(int pipefd[2], int *fd, pid_t pid, int *status)
{
	signal(SIGINT, SIG_IGN);
	close(pipefd[1]);
	waitpid(pid, status, 0);
	signal(SIGINT, sigint_handler);
	if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGINT)
	{
		close(pipefd[0]);
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return (130);
	}
	if (WEXITSTATUS(*status) == 130)
	{
		close(pipefd[0]);
		return (130);
	}
	*fd = pipefd[0];
	return (0);
}
