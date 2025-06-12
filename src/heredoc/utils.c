/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:53:32 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/12 18:39:31 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Maneja señal SIGINT en el shell principal.
 * Muestra nueva línea y redibuja prompt de readline.
*/
void	sigint_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	if (g_heredoc_interrupted == 0)
		g_heredoc_interrupted = 130;
}

/*
 * Maneja entrada de caracteres expandiendo buffer si es necesario.
 * Duplica capacidad cuando se alcanza el límite.
*/
int	handle_char_input(char c, char **line, int *i, int *capacity)
{
	char	*temp;

	if (*i >= *capacity - 1)
	{
		*capacity *= 2;
		temp = realloc(*line, *capacity);
		if (!temp)
		{
			free(*line);
			return (0);
		}
		*line = temp;
	}
	(*line)[(*i)++] = c;
	return (1);
}

/*
 * Lee línea para heredoc usando read() carácter por carácter.
*/
char	*heredoc_readline(void)
{
	char	buffer[1];
	char	*line;
	int		i;
	int		capacity;

	line = malloc(100);
	if (!line)
		return (NULL);
	i = 0;
	capacity = 100;
	while (read(STDIN_FILENO, buffer, 1) > 0)
	{
		if (g_heredoc_interrupted || buffer[0] == '\n')
			break ;
		if (!handle_char_input(buffer[0], &line, &i, &capacity))
			return (NULL);
	}
	if (i == 0 || g_heredoc_interrupted)
		return (free(line), NULL);
	line[i] = '\0';
	return (line);
}

/*
 * Maneja señal SIGINT en proceso hijo de heredoc.
 * Establece flag global y termina proceso.
*/
void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	exit(130);
}

/*
 * Escribe línea expandida o original al pipe según disponibilidad.
 * Maneja la expansión de variables y escritura al heredoc.
*/
void	write_heredoc_line(char *line, char *expanded_line, int pipefd)
{
	if (expanded_line)
	{
		write(pipefd, expanded_line, ft_strlen(expanded_line));
		free(expanded_line);
	}
	else
	{
		write(pipefd, line, ft_strlen(line));
	}
	write(pipefd, "\n", 1);
}
