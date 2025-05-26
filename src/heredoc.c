/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:15:33 by ebalana-          #+#    #+#             */
/*   Updated: 2025/05/26 15:37:48 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t g_heredoc_interrupted = 0;

void	heredoc_sigint_handler(int signum)
{
	(void)signum;
	g_heredoc_interrupted = 1;
	write(STDOUT_FILENO, "\n", 1);
	// Cerrar stdin para salir del readline
	close(STDIN_FILENO);
}

int handle_heredoc(char *delimiter, int *heredoc_fd)
{
	int		pipefd[2];
	char	*line;
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	// Configurar señales para heredoc
	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	if (pid == 0) // Proceso hijo - lee las líneas del heredoc
	{
		close(pipefd[0]); // Cerrar extremo de lectura
		
		while (1)
		{
			line = readline("> ");
			
			// Si readline devuelve NULL (Ctrl+D o señal)
			if (!line)
			{
				if (g_heredoc_interrupted)
					exit(130); // SIGINT recibido
				break; // EOF (Ctrl+D)
			}
			
			// Verificar si es el delimitador
			if (ft_strcmp(line, delimiter) == 0)
			{
				free(line);
				break;
			}
			
			// Escribir la línea al pipe (con newline)
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
			
			free(line);
		}
		
		close(pipefd[1]);
		exit(0);
	}
	else // Proceso padre
	{
		close(pipefd[1]); // Cerrar extremo de escritura
		
		// Esperar al proceso hijo
		waitpid(pid, &status, 0);
		
		// Restaurar señales originales
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		
		// Verificar si fue interrumpido por SIGINT
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			close(pipefd[0]);
			return (130); // Código de salida para SIGINT
		}
		
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			close(pipefd[0]);
			return (130);
		}
		
		*heredoc_fd = pipefd[0];
		return (0);
	}
}

int process_all_heredocs(t_cmd *cmd)
{
	t_cmd *current = cmd;
	t_redir *redir;
	int heredoc_fd;
	int result;

	while (current)
	{
		redir = current->redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				result = handle_heredoc(redir->file, &heredoc_fd);
				if (result != 0)
					return (result); // Error o interrupción                
				// Guardar el fd del heredoc para usar después
				current->fd_in = heredoc_fd;
			}
			redir = redir->next;
		}
		current = current->next;
	}
	return (0);
}

void cleanup_heredoc_fds(t_cmd *cmd_list)
{
	t_cmd *current = cmd_list;

	while (current)
	{
		if (current->fd_in != -1 && current->fd_in != STDIN_FILENO)
		{
			close(current->fd_in);
			current->fd_in = -1;
		}
		if (current->fd_out != -1 && current->fd_out != STDOUT_FILENO)
		{
			close(current->fd_out);
			current->fd_out = -1;
		}
		current = current->next;
	}
}