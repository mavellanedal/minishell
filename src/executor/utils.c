/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:15:21 by mavellan          #+#    #+#             */
/*   Updated: 2025/06/04 12:53:37 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_redir_type(t_redir *r)
{
	int	fd;

	if (r->type == REDIR_OUT)
		fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (r->type == REDIR_APPEND)
		fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (r->type == REDIR_IN)
		fd = open(r->file, O_RDONLY);
	else if (r->type == REDIR_HEREDOC)
	{
		fd = r->heredoc_fd;
		r->heredoc_fd = -1;
	}
	else
		fd = -1;
	return (fd);
}

int	get_redir_type(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (REDIR_IN);
	else if (ft_strcmp(token, ">") == 0)
		return (REDIR_OUT);
	else if (ft_strcmp(token, ">>") == 0)
		return (REDIR_APPEND);
	else
		return (REDIR_HEREDOC);
}

char	*get_actual_token(char *token)
{
	if (token[0] == '\1')
		return (&token[1]);
	return (token);
}

int	print_newline_error(t_cmd_parse_data *ctx)
{
	int	j;

	j = 0;
	printf("minishell: syntax error near unexpected token 'newline'\n");
	ctx->last_status_ptr[0] = 2;
	while (j < ctx->arg_index)
		free(ctx->args[j++]);
	free(ctx->args);
	free_redir_list(ctx->redir_head);
	free(ctx->new_cmd);
	free_cmd_list(ctx->head);
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}
