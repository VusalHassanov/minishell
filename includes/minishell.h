#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define QUOTE_NONE 0
# define QUOTE_OPEN 1
# define TOKEN_DOUBLE_QUOTE 2
# define TOKEN_SINGLE_QUOTE 3

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

// t_token				*parse_tokens_from_string(const char *arguments);
void				parse_from_string(const char *arguments, t_shell *system);
void				assign_all_token_types(t_token *head);

// Parsing Utils
int					check_token_syntax(t_token *head);

// AST utils
void				cleanup_ast(t_ast *root);

// Lexing
t_token				*create_token_list(const char *arguments);

// Lexing Utils
void				skip_whitespace(const char **string);
void				free_tokens(t_token *tokens);
void				assign_status(char character, t_parse_flags *status);
char				*dquote_handler(char *token_string, t_parse_flags *status);

// Token Checker 1
int					is_whitespace(char character);
int					is_no_quote(t_parse_flags *status);
int					is_open(t_parse_flags *status);
int					is_closed(char *string, t_parse_flags *status);

// Token Checker 2
int					is_quote(char character);
int					is_quote_literal(char character, t_parse_flags *status);
int					is_quote_matching(char character, t_parse_flags *status);
int					is_shell_operator(char character);

// AST
t_ast				*create_ast(t_token *start, t_token *end);

// Expansion
void				filter_quotes(char *dest, const char *source,
						int *quote_flag);

//Signals
void				handle_sigint(int sig);
int					check_signal_received(void);
void				setup_parent_signals(void);
void				setup_child_signals(void);

// built-ins
int 				ft_cd(t_token *args, char ***envp);
int 				ft_echo(t_token *args);
int					ft_env(char **envp);
int 				ft_exit_tokens(t_token *args);
int 				ft_export(t_token *args, char ***envp);
int 				ft_pwd();
int 				ft_unset(t_token *args, char ***envp);

// Helper functions
void				ft_free_split(char **arr);
char				*ft_strjoin_three(const char *s1, const char *sep, const char *s2);

// Echo helper
int					is_n_flag(const char *arg);

// Exit helper
int					is_numeric(const char *str);

// CD helper
char				*cd_get_target(t_token *args, char **envp);

// Export helpers
void				export_print_all(char **envp);
void				split_name_value(const char *str, char **name, char **value);

// Env helpers
char				**ft_envdup(char **envp);
char				*ft_getenv(char **envp, const char *name);
char				**ft_env_add(char **envp, char *new_var);
int					ft_env_replace(char **envp, const char *name, char *new_var);
int					ft_setenv(char ***envp, const char *name, const char *value);

// Env helpers 2
void				update_env(char ***envp, char *oldpwd);
char				**envp_remove(char **envp, const char *name);
void				bubble_sort_envp(char **envp);
int					is_valid_name(const char *name);


#endif
