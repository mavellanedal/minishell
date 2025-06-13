/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:42:36 by mavellan          #+#    #+#             */
/*   Updated: 2025/06/13 15:21:53 by ebalana-         ###   ########.fr       */
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
# include <errno.h>

# define UNCLOSED_QUOTES	"Error: Unclosed quotes\n"
# define UNSET				"unset: `%s`: not a valid identifier\n"
# define ENV				"env: %s: No such file or directory\n"
# define REDIR_IN 1
# define REDIR_OUT 2
# define REDIR_APPEND 3
# define REDIR_HEREDOC 4

// Redirección (<, >, >>, <<) con su archivo de destino
typedef struct s_redir
{
	int				type;
	char			*file;
	int				heredoc_fd;
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

typedef struct s_cmd_parse_data
{
	t_cmd	*head;
	t_cmd	*current;
	t_cmd	*new_cmd;
	t_redir	*redir_head;
	char	**tokens;
	char	**args;
	int		arg_index;
	int		i;
	int		*last_status_ptr;
}	t_cmd_parse_data;

// Env estructura
typedef struct s_env
{
	char			*key;
	char			*value;
	int				has_value;
	struct s_env	*next;
}	t_env;

typedef struct s_processing_state
{
	const char	*token;
	char		*result;
	int			i;
	int			j;
	bool		in_single;
	bool		in_double;
	bool		escaped;
	bool		had_quotes;
	int			last_status;
	t_env		*env;
}	t_processing_state;

typedef struct s_expand_params
{
	const char	*str;
	int			*i;
	int			len;
	char		*result;
	int			last_status;
	t_env		*env;
}	t_expand_params;

// Estado interno usado para separar tokens (normi)
typedef struct s_token_state
{
	int		i;
	int		j;
	int		start;
	int		last_status;
	t_env	*env;
}	t_token_state;

// Estado de comillas utilizado durante el tokenizado (normi)
typedef struct s_quote_state
{
	bool	in_single;
	bool	in_double;
}	t_quote_state;

typedef struct s_exec_data
{
	t_cmd	*cmd;
	char	**envp;
	int		prev_read;
	int		pipe_fds[2];
	t_env	*env_list;
	int		exit_status;
}	t_exec_data;

// Estructura para pasar parámetros a las funciones de heredoc
typedef struct s_heredoc_data
{
	t_cmd	*cmd_head;
	t_redir	*redir;
	char	*delimiter;
	int		pipefd[2];
	t_env	*env;
	int		*fd;
}	t_heredoc_data;

// main.c
int				execute_with_heredocs(t_cmd *cmd_list, t_env **env_list);
void			expand_all_tokens(char **tokens, int status, t_env *env_list);
int				handle_input_line(char *line, int last_status, \
	t_env **env_list);
void			shell_loop(t_env *env_list, int last_status);
int				main(int argc, char **argv, char **envp);

// parser/check_pipes_redirections.c
bool			operator_check(char *token);
int				validate_invalid_operators(char *token);
int				validate_redirection_syntax(char **tokens, int i);
int				validate_pipe_syntax(char **tokens, int i);
int				validate_syntax(char **tokens);

// parser/handle_expand_heredoc.c
void			handle_escape(t_processing_state *state);
void			handle_variable(t_processing_state *state);
void			handle_exit_status(t_expand_params *params);
void			handle_named_variable(t_expand_params *params);

// parser/process_expand.c
int				expand_variable(t_expand_params *params);
void			finalize_result(t_processing_state *state);
void			toggle_quotes(t_processing_state *state);
void			process_loop(t_processing_state *state);
char			*process_token_properly(const char *token, \
	int last_status, t_env *env);

// parser/read_token.c
bool			handle_quotes(const char *input, int *i, bool *inside_quotes, \
	char *quote_char);
bool			handle_operator(const char *input, int *i, int start, \
	bool inside_quote);
void			read_token(const char *input, int *i, int *start);
void			process_heredoc(const char *input, t_token_state *s, \
	char **tokens);

// parser/tokenize.c
void			init_token_state(t_token_state *s, int last_status, t_env *env);
void			fill_token_array(const char *input, char **tokens, \
	t_token_state *s);
int				validate_token_array(char **tokens);
char			**tokenize_input(const char *input, int last_status, \
	t_env *env);

// parser/utils.c
void			skip_spaces(const char *input, int *i);
void			save_token(char **tokens, t_token_state *s, \
	const char *input, int end);
t_quote_state	get_quote_state(const char *str, int up_to);

// built_ins/utils.c
int				ft_echo(char **args);
int				ft_pwd(void);
int				ft_exit(char **args);
int				ft_unset(char **args, t_env **env_list);
int				execute_builtin(char **args, t_env **env_list);

// built_ins/env_handler.c
t_env			*create_node_env(char *env_var);
t_env			*create_env_list(char **envp);
int				ft_env(t_env *env_list);
int				is_valid_identifier(const char *str);
void			remove_env_key(t_env **env_list, const char *key);

// built_ins/cd_handler.c
char			*get_env_value(t_env *env, const char *key);
void			update_env_var(t_env **env, const char *key, \
const char *new_value);
char			*get_cd_target(char **args, t_env *env);
void			update_pwd_vars(t_env **env, char *oldpwd);
int				ft_cd(char **args, t_env **env);

// built_ins/export_handler.c
int				is_valid_identifier_export(const char *str);
void			print_export_sorted(t_env *env);
int				ft_export(char **args, t_env **env);
void			free_env_array(char **env_array);

// built_ins/envp_utils.c
void			update_existing_env(t_env *curr, const char *value, \
	int has_value);
void			create_new_env_node(t_env **env, const char *key, \
	const char *value, int has_value);
void			add_or_update_env(t_env **env, const char *key, \
	const char *value, int has_value);
t_env			*create_env_node(const char *key, const char *value);

// built_ins/export_utils.c
int				get_env_list_len(t_env *env);
t_env			**copy_env_to_array(t_env *env, int len);
void			sort_env_array(t_env **arr, int len);
void			print_sorted_env(t_env **arr, int len);

// built_ins/export_main_function_utils.c
int				handle_no_assignment(char *arg, t_env **env);
int				handle_assignment(char *arg, t_env **env);
int				handle_invalid_identifier(char *arg);
int				print_and_return(t_env **env);
int				handle_export_argument(char *arg, t_env **env);

// executor/child_process.c
void			redirect_io(t_cmd *cmd, t_exec_data *exec_data);
void			execute_if_builtin(t_cmd *cmd, t_exec_data *exec_data);
void			check_executable_errors(char *path, char **envp);
void			execute_command(t_cmd *cmd, char **envp_array, \
	char *full_path);
void			setup_child_process(t_cmd *cmd, t_exec_data *exec_data);

// executor/command_path.c
char			*get_path_variable(t_env *env_list);
char			*search_executable_in_paths(char **paths, char *cmd);
char			*find_command_path(char *cmd, t_env *env_list);
char			*get_full_command_path(char *cmd_name, t_env *env_list);

// executor/envp_handler.c
char			**convert_env_to_envp(t_env *env);
int				fill_envp_array(t_env *env, char **envp);
char			**free_partial_envp(char **envp, int until);
int				count_env_vars(t_env *env);

// executor/executor.c
void			wait_and_get_status(pid_t pid, int *last_status);
void			setup_pipe(t_cmd *cmd, t_exec_data *exec_data);
int				check_pipe_syntax(t_cmd *cmd);
int				executor(t_cmd *cmd_list, t_env **env_list);

// executor/handle_child_process.c
void			handle_command_not_found(t_cmd *cmd, char **envp_array);
void			handle_execve_sh_fallback(char *full_path, \
	char **envp_array);
pid_t			fork_and_execute_command(t_cmd *cmd, t_exec_data *exec_data);

// executor/handlers.c
int				handle_builtin(t_cmd *cmd, t_env **env_list);
int				handle_command(t_cmd *cmd, t_exec_data *exec_data, \
	t_env **env_list);
void			handle_pipe_end(t_cmd *cmd, t_exec_data *exec_data);
int				handle_redirection_only(t_cmd *cmd, t_exec_data *exec_data);
int				handle_full_command(t_cmd *cmd, t_exec_data *exec_data);

// executor/pipeline.c
int				count_commands(t_cmd *cmd_list);
int				wait_for_all_processes(pid_t *pids, int cmd_count);
pid_t			*fork_all_processes(t_cmd *cmd_list, t_env **env_list, \
	int cmd_count);
int				execute_pipeline(t_cmd *cmd_list, t_env **env_list);
int				handle_no_pipe(t_cmd *cmd, t_env **env_list);
// executor/redirections.c
void			handle_output_redirection(t_redir *r, int *last_out_fd, \
	int fd);
void			handle_input_redirection(t_redir *r, int *last_in_fd, \
	int fd);
void			apply_all_redirs(t_redir *r, int *last_out_fd, \
	int *last_in_fd);
void			apply_redirections(t_cmd *cmd);
bool			is_redirection_operator(char *token);

// executor/tokens_to_cmd.c
int				handle_redirection(t_cmd_parse_data *ctx, char *actual_token);
int				fill_args_and_redirs(t_cmd_parse_data *ctx);
bool			prepare_new_command(t_cmd_parse_data *ctx);
void			initialize_cmd_parse_data(t_cmd_parse_data *data, \
					char **tokens, int *last_status);
t_cmd			*parse_tokens_to_cmd_list(char **tokens, int *last_status);

// executor/utils.c
int				check_redir_type(t_redir *r);
int				get_redir_type(char *token);
char			*get_actual_token(char *token);
int				print_newline_error(t_cmd_parse_data *ctx);
int				is_builtin(char *cmd);

//executor/free.c
void			free_args(char **args);
void			free_cmd_list(t_cmd *cmd);
void			free_redir_list(t_redir *redir_list);
void			free_tokens(char **tokens);

extern volatile sig_atomic_t	g_heredoc_interrupted;

// heredoc/clean.c
void			init_heredoc_basic(t_heredoc_data *data, t_cmd *cmd_head, \
	t_redir *redir, t_env *env);
void			set_heredoc_fd(t_heredoc_data *data, int *fd);
void			cleanup_heredoc_fds(t_cmd *cmd_list);
void			clear_redirs_fds(t_cmd *cmd_head, t_redir *current_redir);

// heredoc/heredoc.c
void			run_heredoc_child(t_heredoc_data *data);
int				handle_heredoc(t_heredoc_data *data);
int				run_heredoc_parent(pid_t pid, int *fd, int pipefd[2]);
int				process_cmd_heredocs(t_cmd *cmd_head, t_redir *redir, \
	t_env *env);
int				process_heredocs(t_cmd *cmd_list, t_env *env);

// heredoc/utils.c
void			sigint_handler(int signum);
int				handle_char_input(char c, char **line, int *i, int *capacity);
char			*heredoc_readline(void);
void			heredoc_sigint_handler(int sig);
void			write_heredoc_line(char *line, char *expanded_line, int pipefd);

// shlvl.c
int				increment_shlvl_if_exists(t_env *env);
void			add_shlvl_node(t_env **env_list);
void			update_shlvl(t_env **env_list);

// free_env.c
void			free_env_array(char **env_array);
void			free_env_list(t_env *env);

#endif
