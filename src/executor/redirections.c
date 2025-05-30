/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:49:11 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/29 18:31:37 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_output_redirection(t_redir *r, int *last_out_fd, int fd)
{
	if (r->type == REDIR_OUT || r->type == REDIR_APPEND)
	{
		if (*last_out_fd != -1)
			close(*last_out_fd);
		*last_out_fd = fd;
	}
}

void	handle_input_redirection(t_redir *r, int *last_in_fd, int fd)
{
	// CAMBIO: Añadir REDIR_HEREDOC aquí
	if (r->type == REDIR_IN || r->type == REDIR_HEREDOC)
	{
		if (*last_in_fd != -1)
			close(*last_in_fd);
		*last_in_fd = fd;
	}
}

void	apply_all_redirs(t_redir *r, int *last_out_fd, int *last_in_fd)
{
	int	fd;

	while (r)
	{
		// printf("DEBUG: redir type=%d, file=%s\n", r->type, r->file);
		fd = check_redir_type(r);
		if (fd < 0)
		{
			if (errno != 0)
				perror("minishell: redirection");
			else
				ft_putstr_fd("minishell: redirection error\n", STDERR_FILENO);
			exit(1);
		}
		handle_output_redirection(r, last_out_fd, fd);
		handle_input_redirection(r, last_in_fd, fd);
		
		// CAMBIO: No cerrar el fd si es heredoc porque se usa más tarde
		if (r->type != REDIR_OUT && r->type != REDIR_APPEND && 
			r->type != REDIR_IN && r->type != REDIR_HEREDOC)
			close(fd);
		r = r->next;
	}
}

void	apply_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int		last_out_fd;
	int		last_in_fd;

	r = cmd->redirs;
	last_out_fd = -1;
	last_in_fd = -1;

	apply_all_redirs(r, &last_out_fd, &last_in_fd);

	if (last_out_fd != -1)
	{
		dup2(last_out_fd, STDOUT_FILENO);
		close(last_out_fd);
	}
	if (last_in_fd != -1)
	{
		dup2(last_in_fd, STDIN_FILENO);
		close(last_in_fd);
	}
}
