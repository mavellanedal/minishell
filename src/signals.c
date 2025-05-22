/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:56:26 by ebalana-          #+#    #+#             */
/*   Updated: 2025/05/21 15:05:31 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);                      // Salto de línea
	rl_replace_line("", 0);                // Limpia la línea actual de readline
	rl_on_new_line();                      // Mueve el cursor a una nueva línea
	rl_redisplay();                        // Redibuja el prompt
}