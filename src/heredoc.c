/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:15:33 by ebalana-          #+#    #+#             */
/*   Updated: 2025/05/29 18:16:20 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t g_heredoc_interrupted = 0;

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

// Función simple para leer línea por línea sin get_next_line
char	*read_line_from_stdin(void)
{
	char *line = NULL;
	char buffer[1];
	int i = 0;
	int capacity = 100;

	line = malloc(capacity);
	if (!line)
		return NULL;

	while (read(STDIN_FILENO, buffer, 1) > 0)
	{
		if (buffer[0] == '\n')
		{
			line[i] = '\0';
			return line;
		}
		
		if (i >= capacity - 1)
		{
			capacity *= 2;
			char *temp = realloc(line, capacity);
			if (!temp)
			{
				free(line);
				return NULL;
			}
			line = temp;
		}
		
		line[i++] = buffer[0];
	}

	// EOF reached
	if (i == 0)
	{
		free(line);
		return NULL;
	}

	line[i] = '\0';
	return line;
}

int	handle_heredoc(char *delimiter, int *fd)
{
	int pipefd[2];
	pid_t pid;
	char *line;
	int status;
	
	printf("DEBUG: delimiter=[%s]\n", delimiter); // Debug
	
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return -1;
	}
	
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return -1;
	}
	
	if (pid == 0) // Child process
	{
		signal(SIGINT, heredoc_sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		close(pipefd[0]);
		
		while (1)
		{
			write(STDOUT_FILENO, "> ", 2);
			line = read_line_from_stdin();
			
			if (!line) // EOF (Ctrl+D)
			{
				printf("DEBUG: EOF reached\n");
				break;
			}
			
			printf("DEBUG: line=[%s], delimiter=[%s]\n", line, delimiter); // Debug
			printf("DEBUG: strcmp result=%d\n", ft_strcmp(line, delimiter)); // Debug
			
			if (ft_strcmp(line, delimiter) == 0)
			{
				printf("DEBUG: Match found, breaking\n"); // Debug
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
	else // Parent process
	{
		close(pipefd[1]);
		waitpid(pid, &status, 0);
		
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			close(pipefd[0]);
			return 130;
		}
		
		*fd = pipefd[0];
		return 0;
	}
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
				if (result == 130) // SIGINT
					return 130;
				if (result != 0)
					return result;
					
				// Store the fd for later use
				redir->heredoc_fd = fd;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return 0;
}
