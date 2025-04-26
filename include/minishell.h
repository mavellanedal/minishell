/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavellan <mavellan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:42:36 by mavellan          #+#    #+#             */
/*   Updated: 2025/04/24 13:44:27 by mavellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/ultimate_libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

# define UNCLOSED_QUOTES	"Error: Unclosed quotes\n"

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
	struct s_cmd	*next;
}	t_cmd;

// Estado interno usado para separar tokens (normi)
typedef struct s_token_state
{
	int	i;
	int	j;
	int	start;
	int	last_status;
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
}	t_expand_state;

typedef struct s_env
{
	char		**env;
	char		**paths;
}	t_env;

typedef struct s_command
{
	char	**tokens;
	char	*infile;
	char	*outfile;
	int		append;
}	t_command;

typedef struct s_data
{
	t_cmd	*cmds;
	int		num_cmds;
	char	**envp;
} t_data;


// parse/tokenize.c
t_quote_state	get_quote_state(const char *str, int up_to);
void			save_token(char **tokens, t_token_state *s, \
const char *input, int end);
void			init_token_state(t_token_state *s, int last_status);
char			**tokenize_input(const char *input, int last_status);

// parse/handle.c
void			handle_end(char **tokens, const char *input, t_token_state *s);
void			handle_redirection(char **tokens, const char *input, \
t_token_state *s);
void			handle_dollar(t_expand_state *s);
void			handle_quote(char c, bool *in_single, bool *in_double, \
bool *has_single);

// parse/expand.c
char			*strip_quotes(const char *token, bool *has_single);
char			*remove_quotes_and_expand(const char *token, int last_status);
int				expand_named_variable(const char *str, int i, \
char *result, int j);
void			process_expansion_loop(t_expand_state *s);
char			*expand_variables(const char *str, int last_status);

// executor/executor.c
char			**complete_paths(char **paths);
char			**get_path_array(char **env);
char			*get_env_value(char **env, const char *name);

#endif
