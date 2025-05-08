/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:15:21 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/02 14:17:03 by mavellan         ###   ########.fr       */
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
