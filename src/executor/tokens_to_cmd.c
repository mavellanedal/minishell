/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:36:52 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/04 16:58:55 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Maneja una redirección durante el parsing.
 * Crea nodo de redirección y lo añade a la lista.
*/
int	handle_redirection(t_cmd_parse_data *ctx, char *actual_token)
{
	t_redir	*new_redir;
	t_redir	*last;

	if (!ctx->tokens[ctx->i + 1])
		return (print_newline_error(ctx));
	new_redir = ft_calloc(1, sizeof(t_redir));
	if (!new_redir)
		return (0);
	new_redir->type = get_redir_type(actual_token);
	new_redir->file = ft_strdup(get_actual_token(ctx->tokens[ctx->i + 1]));
	new_redir->heredoc_fd = -1;
	new_redir->next = NULL;
	if (!ctx->redir_head)
		ctx->redir_head = new_redir;
	else
	{
		last = ctx->redir_head;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
	ctx->i += 2;
	return (1);
}

/*
 * Procesa argumentos y redirecciones hasta encontrar pipe.
 * Llena arrays de argumentos y lista de redirecciones.
*/
int	fill_args_and_redirs(t_cmd_parse_data *ctx)
{
	char	*actual_token;

	while (ctx->tokens[ctx->i] && ft_strcmp(ctx->tokens[ctx->i], "|") != 0)
	{
		actual_token = get_actual_token(ctx->tokens[ctx->i]);
		if (ctx->tokens[ctx->i][0] != '\1' && \
			is_redirection_operator(actual_token))
		{
			if (!handle_redirection(ctx, actual_token))
				return (0);
		}
		else
		{
			ctx->args[ctx->arg_index++] = ft_strdup(actual_token);
			ctx->i++;
		}
	}
	return (1);
}

/*
 * Prepara estructura para un nuevo comando.
 * Inicializa memoria para comando y argumentos.
*/
bool	prepare_new_command(t_cmd_parse_data *ctx)
{
	ctx->new_cmd = calloc(1, sizeof(t_cmd));
	if (!ctx->new_cmd)
	{
		free_cmd_list(ctx->head);
		return (false);
	}
	ctx->args = calloc(100, sizeof(char *));
	if (!ctx->args)
	{
		free(ctx->new_cmd);
		free_cmd_list(ctx->head);
		return (false);
	}
	ctx->arg_index = 0;
	ctx->redir_head = NULL;
	return (true);
}

/*
 * Inicializa estructura de datos para parsing.
 * Configura punteros y contadores iniciales.
*/
void	initialize_cmd_parse_data(t_cmd_parse_data *data, \
	char **tokens, int *last_status)
{
	data->head = NULL;
	data->current = NULL;
	data->redir_head = NULL;
	data->tokens = tokens;
	data->i = 0;
	data->arg_index = 0;
	data->last_status_ptr = last_status;
}

/*
 * Convierte array de tokens en lista enlazada de comandos.
 * Función principal del parser de comandos.
*/
t_cmd	*parse_tokens_to_cmd_list(char **tokens, int *last_status)
{
	t_cmd_parse_data	ctx;

	initialize_cmd_parse_data(&ctx, tokens, last_status);
	while (ctx.tokens[ctx.i])
	{
		if (!prepare_new_command(&ctx))
			return (NULL);
		if (!fill_args_and_redirs(&ctx))
			return (NULL);
		ctx.args[ctx.arg_index] = NULL;
		ctx.new_cmd->args = ctx.args;
		ctx.new_cmd->redirs = ctx.redir_head;
		ctx.new_cmd->fd_in = -1;
		ctx.new_cmd->fd_out = -1;
		ctx.new_cmd->next = NULL;
		if (!ctx.head)
			ctx.head = ctx.new_cmd;
		else
			ctx.current->next = ctx.new_cmd;
		ctx.current = ctx.new_cmd;
		if (ctx.tokens[ctx.i] && ft_strcmp(ctx.tokens[ctx.i], "|") == 0)
			ctx.i++;
	}
	return (ctx.head);
}
