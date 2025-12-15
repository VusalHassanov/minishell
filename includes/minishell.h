#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/types.h>

# define QUOTE_NONE 0
# define QUOTE_OPEN 1
# define TOKEN_DOUBLE_QUOTE 2
# define TOKEN_SINGLE_QUOTE 3

# define SUCCESS 0
# define FAILURE 1
# define ERROR -1
# define FALSE 0
# define TRUE 1
# define LEFT 0
# define RIGHT 1


typedef enum e_token_type
{
	TOKEN_NONE,
	TOKEN_WORD,
	TOKEN_COMMAND,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
}					t_token_type;

typedef struct s_redir
{
	int				type;
	char			*target;
	int				heredoc_fd;
}					t_redir;

typedef struct s_ast
{
	int				node_type;
	char			**argv;
	t_redir			**redir;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct s_shell
{
	struct s_token	*token_list;
	struct s_ast	*ast_root;
	int				exit_status;
	char			**envp;
	int				is_child;

}					t_shell;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	int				quote_flag;
}					t_token;

typedef struct s_parse_flags
{
	unsigned int	double_quote;
	unsigned int	single_quote;
}					t_parse_flags;

// Parsing
int					parse_from_string(const char *arguments, t_shell *system);

// Parsing Utils
int					check_token_syntax(t_token *head);

// Lexing
t_token				*create_token_list(const char *arguments);

// Lexing Utils
void				skip_whitespace(const char **string);
void				free_tokens(t_token *tokens);
void				assign_status(char character, t_parse_flags *status);
char				*dquote_handler(char *token_string, t_parse_flags *status);
char				*get_token_string(const char *arguments, t_parse_flags *status);

// Token Checker 1
int					is_whitespace(char character);
int					is_no_quote(t_parse_flags *status);
int					is_open(t_parse_flags *status);
int					is_closed(char *string, t_parse_flags *status);
int					is_quote_literal(char character, t_parse_flags *status);

// Token Checker 2
int					is_quote(char character);
// int					is_quote_literal(char character, t_parse_flags *status);
int					is_quote_matching(char character, t_parse_flags *status);
int					is_shell_operator(char character);
int					is_redirection_operator(t_token_type type);

// AST
t_ast			*create_ast(t_token *start, t_token *end, t_shell *system);

// AST utils
void				cleanup_ast(t_ast *root);
void				ft_free_redirections(t_redir **redir);
t_redir				**cleanup_redir_error(t_redir **redirection, char *target);
char				**cleanup_argv_error(char **argv);

// Execution
void				execute_ast(t_ast *node, t_shell *system);
int					is_builtin(char *command);
int					execute_builtin(char **argv, char ***envp);
int					execute_external(t_ast *node, t_shell *system);
char				*resolve_path(char **envp, char *cmd);
int					set_up_redirections(t_ast *node, t_shell *system);
// int					count_similar_commands(char **envp, char *cmd);

// Execution Helper
int					ft_reset_fds(int *fd);
int					ft_backup_fds(int *fd);

// Pipes
void				create_pipe(t_ast *node, t_shell *system);

// redirections
int					ft_heredoc(int heredoc_fd, t_shell *system);
int					get_input_heredoc_fd(char *delimitter, t_shell *system);
int					heredoc_gsignal_error(char *line, int write_fd, int read_fd);
char				*expand_if_needed(char *line, int expand_flag, t_shell *system);
int					ft_delimiter_is_quoted(char *delimiter);
int					generate_temp_file(int *write_fd, int *read_fd);
int					ft_redir_append(char *target);
int					ft_redir_out(char *target);
int					ft_redir_in(char *target);

// Expansion
// void				filter_quotes(char *dest, const char *source,
// 						int *quote_flag);
char				*expand_env_var(char *str, int pos, char **env);
char				*extract_var_name(char *str, int start);
char				*expand_exit_status(char *str, int pos, int exit_status);
void				copy_exit_status(char *dst, char *src, char *exit_str,
						int pos);
void				handle_expansion(char **argv, t_shell *system);
char				*expand_string(char *str, t_shell *system, int expand_flag);
char				*expand_variable(char *str, int *i, t_shell *system, int in_heredoc);
int					get_var_len(char *str, int pos);
void				copy_with_var(char *dst, char *src, char *value, int pos);
char				*remove_var(char *str, int pos);
char				*replace_var(char *str, int pos, char *value);
void				copy_without_var(char *dst, char *src, int pos,
						int var_len);
int					is_in_single_quotes(char *str, int pos);
char				*remove_quotes(char *str);

// Signals
extern volatile sig_atomic_t	g_signal;
void				handle_sigint(int sig);
void				handle_heredoc_sigint(int sig);
int					check_signal_received(void);
void				setup_parent_signals(void);
void				setup_child_signals(void);
void				setup_heredoc_signals(void);

void 				setup_dquote_signals(void);
void				handle_dquote_sigint(int sig);

// built-ins
int					ft_cd(char **args, char ***envp);
int					ft_echo(char **argv);
int					ft_env(char **envp);
int					ft_exit(char **argv);
int					ft_export(char **argv, char ***envp);
int					ft_pwd(void);
int					ft_unset(char **argv, char ***envp);

// built-in helper
char				*cd_get_target(char **argv, char **envp);
char				*expand_tilde(char *path, char **envp);
int					is_n_flag(const char *arg);
int					is_numeric(const char *str);

// Helper funtions
void				ft_free_split(char **arr);
char				*ft_strjoin_three(const char *s1, const char *sep,
						const char *s2);

// Export helpers
void				export_print_all(char **envp);
void				split_name_value(const char *str, char **name,
						char **value);

// Env helpers
char				**ft_envdup(char **envp);
char				*ft_getenv(char **envp, const char *name);
char				**ft_env_add(char **envp, char *new_var);
int					ft_env_replace(char **envp, const char *name,
						char *new_var);
int					ft_setenv(char ***envp, const char *name,
						const char *value);

// Env helpers 2
void				update_env(char ***envp, char *oldpwd);
char				**envp_remove(char **envp, const char *name);
void				bubble_sort_envp(char **envp);
int					is_valid_name(const char *name);

#endif
