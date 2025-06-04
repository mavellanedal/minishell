/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_child_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:12:14 by ebalana-          #+#    #+#             */
/*   Updated: 2025/06/04 16:56:22 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Maneja comando no encontrado.
 * Muestra error y termina proceso hijo con código 127.
*/
void	handle_command_not_found(t_cmd *cmd, char **envp_array)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_free(envp_array);
	exit(127);
}

/*
 * Maneja fallback con /bin/sh cuando execve falla.
 * Intenta ejecutar como script de shell.
*/
void	handle_execve_sh_fallback(char *full_path, char **envp_array)
{
	char	*new_argv[3];

	new_argv[0] = "/bin/sh";
	new_argv[1] = full_path;
	new_argv[2] = NULL;
	execve("/bin/sh", new_argv, envp_array);
}

/*
 * Crea proceso hijo y ejecuta comando.
 * Maneja fork, configuración del hijo y ejecución.
*/
pid_t	fork_and_execute_command(t_cmd *cmd, t_exec_data *exec_data)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		setup_child_process(cmd, exec_data);
	}
	return (pid);
}
