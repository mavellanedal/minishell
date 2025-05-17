/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:15:21 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/17 15:50:53 by mavellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_redir_type(t_redir *r)
{
	int	fd;

	// ft_printf("Dentro de check_redir_type\n");
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

t_cmd	*parse_tokens_to_cmd_list(char **tokens)
{
	t_cmd	*head = NULL;
	t_cmd	*current = NULL;
	int		i = 0;

	while (tokens[i])
	{
		t_cmd *new_cmd = calloc(1, sizeof(t_cmd));
		if (!new_cmd)
			return (NULL); // Error malloc

		// Crear listas dinámicas temporales
		char **args = calloc(100, sizeof(char *)); // puedes hacer realloc más adelante
		t_redir *redir_head = NULL;
		int arg_index = 0;

		while (tokens[i] && strcmp(tokens[i], "|") != 0)
		{
			if (strcmp(tokens[i], "<") == 0 || strcmp(tokens[i], ">") == 0 ||
				strcmp(tokens[i], ">>") == 0 || strcmp(tokens[i], "<<") == 0)
			{
				int redir_type;
				if (!tokens[i + 1])
					return (NULL); // error de sintaxis
				if (strcmp(tokens[i], "<") == 0)
					redir_type = REDIR_IN;
				else if (strcmp(tokens[i], ">") == 0)
					redir_type = REDIR_OUT;
				else if (strcmp(tokens[i], ">>") == 0)
					redir_type = REDIR_APPEND;
				else
					redir_type = REDIR_HEREDOC;

				t_redir *new_redir = calloc(1, sizeof(t_redir));
				new_redir->type = redir_type;
				new_redir->file = strdup(tokens[i + 1]);
				new_redir->next = redir_head;
				redir_head = new_redir;

				i += 2;
			}
			else
			{
				args[arg_index++] = strdup(tokens[i]);
				i++;
			}
		}
		args[arg_index] = NULL;

		new_cmd->args = args;
		new_cmd->redirs = redir_head;
		new_cmd->next = NULL;

		if (!head)
			head = new_cmd;
		else
			current->next = new_cmd;
		current = new_cmd;

		if (tokens[i] && strcmp(tokens[i], "|") == 0)
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

/*int	is_builtin(char **tokens)
{
	if (!tokens || !tokens[0])
		return (-1);
	if (ft_strcmp(tokens[0], "echo"))
		return (1)
}*/