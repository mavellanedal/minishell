/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:49:11 by mavellan          #+#    #+#             */
/*   Updated: 2025/06/04 18:39:48 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Maneja redirecciones de salida (>, >>).
 * Cierra descriptor anterior y actualiza last_out_fd.
*/
void	handle_output_redirection(t_redir *r, int *last_out_fd, int fd)
{
	if (r->type == REDIR_OUT || r->type == REDIR_APPEND)
	{
		if (*last_out_fd != -1)
			close(*last_out_fd);
		*last_out_fd = fd;
	}
}

/*
 * Maneja redirecciones de entrada (<, <<).
 * Cierra descriptor anterior y actualiza last_in_fd.
*/
void	handle_input_redirection(t_redir *r, int *last_in_fd, int fd)
{
	if (r->type == REDIR_IN || r->type == REDIR_HEREDOC)
	{
		if (*last_in_fd != -1)
			close(*last_in_fd);
		*last_in_fd = fd;
	}
}

/*
 * Aplica todas las redirecciones de un comando.
 * Procesa entrada y salida, maneja múltiples redirecciones.
*/
void	apply_all_redirs(t_redir *r, int *last_out_fd, int *last_in_fd)
{
	int	fd;

	while (r)
	{
		fd = check_redir_type(r);
		if (fd < 0)
		{
			if (errno != 0)
				perror("minishell: redirection");
			else
				ft_putstr_fd("minishell: redirection error\n", STDERR_FILENO);
			exit(1);
		}
		if (r->type == REDIR_OUT || r->type == REDIR_APPEND)
			handle_output_redirection(r, last_out_fd, fd);
		else if (r->type == REDIR_IN || r->type == REDIR_HEREDOC)
			handle_input_redirection(r, last_in_fd, fd);
		r = r->next;
	}
}

/*
 * Aplica redirecciones y actualiza stdin/stdout.
 * Función principal para configurar redirecciones.
*/
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

/*
 * Verifica si un token es un operador de redirección.
 * Detecta <, >, >>, <<.
*/
bool	is_redirection_operator(char *token)
{
	return (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0 || \
		ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<<") == 0);
}
