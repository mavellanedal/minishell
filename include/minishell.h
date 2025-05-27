/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:42:36 by mavellan          #+#    #+#             */
/*   Updated: 2025/05/27 13:33:57 by mavellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/ultimate_libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
#include <errno.h>

# define UNCLOSED_QUOTES	"Error: Unclosed quotes\n"
# define UNSET				"unset: `%s`: not a valid identifier\n"
# define ENV				"env: %s: No such file or directory\n"
#define REDIR_IN 1
#define REDIR_OUT 2
#define REDIR_APPEND 3
#define REDIR_HEREDOC 4

// Redirección (<, >, >>, <<) con su archivo de destino
typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

// Comando con sus argumentos y redirecciones
typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}	t_cmd;

// Env estructura
typedef struct s_env
{
	char			*key;
	char			*value;
	int				has_value;
	struct s_env	*next;
}	t_env;

// Estado interno usado para separar tokens (normi)
typedef struct s_token_state
{
	int	i;
	int	j;
	int	start;
	int	last_status;
	t_env	*env;
}	t_token_state;

// Estado de comillas utilizado durante el tokenizado (normi)
typedef struct s_quote_state
{
	bool	in_single;
	bool	in_double;
}	t_quote_state;

// Estado interno usado durante la expansión de variables (normi)
typedef struct s_expand_state
{
	const char	*str;
	int			*i;
	char		*res;
	int			j;
	int			last_status;
	t_env		*env;
}	t_expand_state;

typedef struct s_data
{
	t_cmd	*cmds;
	int		num_cmds;
	char	**envp;
}	t_data;

typedef struct s_exec_data
{
	t_cmd	*cmd;
	char	**envp;
	int		prev_read;
	int		pipe_fds[2];
	t_env	*env_list;
	int		exit_status;
}	t_exec_data;


// parse/tokenize.c
t_quote_state	get_quote_state(const char *str, int up_to);
void			save_token(char **tokens, t_token_state *s, const char *input, int end, t_env *env);
void			init_token_state(t_token_state *s, int last_status, t_env *env);
char			**tokenize_input(const char *input, int last_status, t_env *env);

// parse/handle.c
void			handle_end(char **tokens, const char *input, t_token_state *s, t_env *env);
void			handle_redirection(char **tokens, const char *input, t_token_state *s, t_env *env);
void			handle_dollar(t_expand_state *s);
void			handle_quote(char c, bool *in_single, bool *in_double, \
bool *has_single);

// parse/expand.c
char			*strip_quotes(const char *token, bool *has_single);
char			*remove_quotes_and_expand(const char *token, int last_status, t_env *env);
int				expand_named_variable(const char *str, int i, char *result, int j, t_env *env);
void			process_expansion_loop(t_expand_state *s);
char			*expand_variables(const char *str, int last_status, t_env *env);

// built_ins/utils.c
int				ft_echo(char **args);
int				ft_pwd(void);
int				ft_exit(char **args);
int				ft_unset(char **args, t_env **env_list);
int				execute_builtin(char **args, t_env **env_list); //int				execute_builtin(char **args, t_env *env_list);

// built_ins/env_handler.c
t_env			*create_node_env(char *env_var);
t_env			*create_env_list(char **envp);
int				ft_env(t_env *env_list);
int				is_valid_identifier(const char *str);
void			remove_env_key(t_env **env_list, const char *key);

// built_ins/cd_handler.c
char			*get_env_value(t_env *env, const char *key);
void			update_env_var(t_env *env, const char *key, \
const char *new_value);
char			*get_cd_target(char **args, t_env *env);
void			update_pwd_vars(t_env *env, char *oldpwd);
int				ft_cd(char **args, t_env *env);

// built_ins/export_handler.c
int				ft_export(char **args, t_env **env);
char			**env_list_to_array(t_env *env_list);
void			free_env_array(char **env_array);

// executor/executor.c
void			apply_redirections(t_cmd *cmd);
void			wait_and_get_status(pid_t pid, int *last_status);
void			setup_pipe(t_cmd *cmd, t_exec_data *exec_data);
int				check_pipe_syntax(t_cmd *cmd);
int				executor(t_cmd *cmd_list, t_env **env_list);

// executor/envp_handler.c
char			**convert_env_to_envp(t_env *env);
int				fill_envp_array(t_env *env, char **envp);
char			**free_partial_envp(char **envp, int until);
int				count_env_vars(t_env *env);

// executor/utils.c
int				check_redir_type(t_redir *r);
t_cmd			*parse_tokens_to_cmd_list(char **tokens, int *last_status);
void			free_cmd_list(t_cmd *cmd);
int				is_builtin(char *cmd);

// executor/child_process.c
void			redirect_io(t_cmd *cmd, t_exec_data *exec_data);
void			execute_if_builtin(t_cmd *cmd, t_exec_data *exec_data);
void			check_executable_errors(char *path, char **envp);
void			setup_child_process(t_cmd *cmd, t_exec_data *exec_data);
pid_t			fork_and_execute_command(t_cmd *cmd, t_exec_data *exec_data);

// executor/command_path.c
char			*find_command_path(char *cmd, t_env *env_list);
char			*get_full_command_path(char *cmd_name, t_env *env_list);

// executor/handlers.c
int				handle_command(t_cmd *cmd, t_exec_data *exec_data, t_env **env_list);
int				handle_builtin(t_cmd *cmd, t_env **env_list);
int				handle_redirection_only(t_cmd *cmd, t_exec_data *exec_data);
int				handle_full_command(t_cmd *cmd, t_exec_data *exec_data);
void			handle_pipe_end(t_cmd *cmd, t_exec_data *exec_data);

// signals
void			sigint_handler(int signum);
int				process_all_heredocs(t_cmd *cmd, t_exec_data *exec_data);
int				handle_heredoc(char *delimiter, int *heredoc_fd);
#endif
