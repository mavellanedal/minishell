/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:01:26 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/13 15:18:17 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Inicializa los campos básicos de heredoc_data.
*/
void	init_heredoc_basic(t_heredoc_data *data, t_cmd *cmd_head, \
	t_redir *redir, t_env *env)
{
	data->cmd_head = cmd_head;
	data->redir = redir;
	data->delimiter = redir->file;
	data->env = env;
}

/*
 * Completa la inicialización con el puntero fd.
*/
void	set_heredoc_fd(t_heredoc_data *data, int *fd)
{
	data->fd = fd;
}

/*
 * Cierra los descriptores de archivo de heredoc abiertos.
 * Limpia los fds de heredoc para evitar fugas de recursos.
*/
void	cleanup_heredoc_fds(t_cmd *cmd_list)
{
	t_redir	*redir;

	while (cmd_list)
	{
		redir = cmd_list->redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC && redir->heredoc_fd > 2)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			redir = redir->next;
		}
		cmd_list = cmd_list->next;
	}
}

/*
 * Cierra los descriptores de archivo de heredoc abiertos,
 * excepto el correspondiente a 'current_redir'.
 * Se utiliza para evitar fugas de recursos al mantener sólo
 * el heredoc necesario abierto.
*/
void	clear_redirs_fds(t_cmd *cmd_head, t_redir *current_redir)
{
	t_redir	*redir;
	t_cmd	*cmd;

	cmd = cmd_head;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir != current_redir && redir->type == REDIR_HEREDOC && \
				redir->heredoc_fd > 2)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
