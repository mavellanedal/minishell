/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:15:21 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/30 08:41:26 by mavellan         ###   ########.fr       */
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
		fd = open (r->file, O_RDONLY);
	else
		fd = -1;
	return (fd);
}

static bool	is_redirection_operator(char *token)
{
	return (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0 ||
			ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<<") == 0);
}

static int	get_redir_type(char *token)
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

static char	*get_actual_token(char *token)
{
	if (token[0] == '\1')
		return (&token[1]);
	return (token);
}

t_cmd	*parse_tokens_to_cmd_list(char **tokens, int *last_status)
{
	t_cmd	*head = NULL;
	t_cmd	*current = NULL;
	int		i = 0;

	while (tokens[i])
	{
		t_cmd *new_cmd = calloc(1, sizeof(t_cmd));
		if (!new_cmd)
		{
			free_cmd_list(head);
			return (NULL);
		}
		char **args = calloc(100, sizeof(char *));
		if (!args)
		{
			free(new_cmd);
			free_cmd_list(head);
			return (NULL);
		}
		t_redir *redir_head = NULL;
		int arg_index = 0;

		while (tokens[i] && ft_strcmp(tokens[i], "|") != 0)
		{
			bool is_literal = (tokens[i][0] == '\1');
			char *actual_token = get_actual_token(tokens[i]);

			// Only treat as operator if NOT literal
			if (!is_literal && is_redirection_operator(actual_token))
			{
				if (!tokens[i + 1])
				{
					ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
					*last_status = 2;
					// Clean up and return
					int j = 0;
					while (j < arg_index)
						free(args[j++]);
					free(args);
					free_redir_list(redir_head);
					free(new_cmd);
					free_cmd_list(head);
					return (NULL);
				}

				t_redir *new_redir = calloc(1, sizeof(t_redir));
				if (!new_redir)
				{
					// Same cleanup as above...
					return (NULL);
				}
				new_redir->type = get_redir_type(actual_token);
				new_redir->file = ft_strdup(get_actual_token(tokens[i + 1]));
				new_redir->next = NULL;

				if (!redir_head)
					redir_head = new_redir;
				else
				{
					t_redir *last = redir_head;
					while (last->next)
						last = last->next;
					last->next = new_redir;
				}
				i += 2;
			}
			else
			{
				// Regular argument
				args[arg_index++] = ft_strdup(actual_token);
				i++;
			}
		}
		args[arg_index] = NULL;

		new_cmd->args = args;
		new_cmd->redirs = redir_head;
		new_cmd->next = NULL;
		new_cmd->fd_in = -1;
		new_cmd->fd_out = -1;

		if (!head)
			head = new_cmd;
		else
			current->next = new_cmd;
		current = new_cmd;

		if (tokens[i] && ft_strcmp(tokens[i], "|") == 0)
			i++;
	}
	return (head);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd *tmp;
	while (cmd)
	{
		tmp = cmd;
		for (int i = 0; cmd->args && cmd->args[i]; i++)
			free(cmd->args[i]);
		free(cmd->args);

		t_redir *r = cmd->redirs;
		while (r)
		{
			t_redir *next = r->next;
			free(r->file);
			free(r);
			r = next;
		}
		cmd = cmd->next;
		free(tmp);
	}
}

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

int	is_builtin(char *cmd)
{
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
