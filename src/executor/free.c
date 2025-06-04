/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:34:56 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/04 16:55:13 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Libera un array de argumentos.
 * Libera cada string y luego el array principal.
*/
void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
		free(args[i++]);
	free(args);
}

/*
 * Libera toda la lista enlazada de comandos.
 * Incluye argumentos, redirecciones y estructuras de comando.
*/
void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*r;
	t_redir	*next;

	while (cmd)
	{
		tmp = cmd;
		free_args(cmd->args);
		r = cmd->redirs;
		while (r)
		{
			next = r->next;
			free(r->file);
			free(r);
			r = next;
		}
		cmd = cmd->next;
		free(tmp);
	}
}

/*
 * Libera una lista enlazada de redirecciones.
 * Libera archivos y estructuras de redirección.
*/
void	free_redir_list(t_redir *redir_list)
{
	t_redir	*current;
	t_redir	*next;

	current = redir_list;
	while (current)
	{
		next = current->next;
		if (current->file)
			free(current->file);
		free(current);
		current = next;
	}
}

/*
 * Libera un array de tokens.
 * Libera cada token y luego el array principal.
*/
void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}
