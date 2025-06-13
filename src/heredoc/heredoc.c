/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:15:33 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/13 15:17:29 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

volatile sig_atomic_t	g_heredoc_interrupted = 0;

/*
 * Maneja proceso padre durante heredoc.
 * Espera al hijo y gestiona señales e interrupciones.
*/
int	run_heredoc_parent(pid_t pid, int *fd, int pipefd[2])
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
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

/*
 * Ejecuta proceso hijo para capturar entrada de heredoc.
 * Lee líneas hasta delimiter y las escribe al pipe.
*/
void	run_heredoc_child(t_heredoc_data *data)
{
	char	*line;
	char	*expanded_line;

	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	close(data->pipefd[0]);
	while (!g_heredoc_interrupted)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = heredoc_readline();
		if (!line || ft_strcmp(line, data->delimiter) == 0)
			break ;
		expanded_line = process_token_properly(line, 0, data->env);
		write_heredoc_line(line, expanded_line, data->pipefd[1]);
		free(line);
	}
	if (line)
		free(line);
	close(data->pipefd[1]);
	clear_redirs_fds(data->cmd_head, data->redir);
	exit(0);
}

/*
 * Maneja la lógica completa de heredoc.
 * Crea pipe, fork y procesa entrada hasta delimiter.
*/
int	handle_heredoc(t_heredoc_data *data)
{
	pid_t	pid;

	if (pipe(data->pipefd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (close(data->pipefd[0]), close(data->pipefd[1]), -1);
	if (pid == 0)
		run_heredoc_child(data);
	return (run_heredoc_parent(pid, data->fd, data->pipefd));
}

/*
 * Procesa heredocs de un comando específico.
 * Ejecuta todos los heredocs encontrados en las redirecciones.
*/
int	process_cmd_heredocs(t_cmd *cmd_head, t_redir *redir, t_env *env)
{
	int				fd;
	int				result;
	t_heredoc_data	data;

	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
		{
			init_heredoc_basic(&data, cmd_head, redir, env);
			set_heredoc_fd(&data, &fd);
			result = handle_heredoc(&data);
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

/*
 * Procesa todos los heredocs de la lista de comandos.
 * Los ejecuta antes del pipeline principal.
*/
int	process_heredocs(t_cmd *cmd_list, t_env *env)
{
	int	result;

	g_heredoc_interrupted = 0;
	while (cmd_list)
	{
		result = process_cmd_heredocs(cmd_list, cmd_list->redirs, env);
		if (result != 0)
			return (result);
		cmd_list = cmd_list->next;
	}
	return (0);
}
