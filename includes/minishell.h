#ifndef MINISHELL_H
# define MINISHELL_H
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "libft.h"

typedef enum e_token_type
{
	TOKEN_NONE,
	TOKEN_COMMAND,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_SINGLE_QUOTE,
	TOKEN_MIXED_QUOTE,
	TOKEN_EMPTY,
	TOKEN_WORD
}					t_token_type;

typedef struct s_tree
{
	struct s_token	*token;
	struct s_tree	*left;
	struct tree_s	*right;
}					t_tree;

typedef struct s_shell
{
	struct s_token	*token_list;
	struct s_tree	*binary_tree;
}					t_shell;

// Parsing
# define QUOTE_NONE 0
# define QUOTE_OPEN 1

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

// Parsing Tokenlist
t_token				*parse_tokens_from_string(const char *arguments);
t_token				*add_token_list(t_token *head, const char *arguments);
void				assign_all_token_types(t_token *head);

// Parsing Utils
void				filter_quotes(char *dest, const char *source,
						int *quote_flag);
void				skip_whitespace(const char **string);
void				free_tokens(t_token *tokens);
void				assign_status(char character, t_parse_flags *status);

//Token Checker 1
int					is_whitespace(char character);
int					is_no_quote(t_parse_flags *status);
int					is_open(t_parse_flags *status);
int					is_closed(char *string, t_parse_flags *status);

//Token Checker 2
int					is_quote(char character);
int					is_quote_literal(char character, t_parse_flags *status);
int					is_quote_matching(char character, t_parse_flags *status);
int					is_shell_operator(char character);


// built-ins (please make some note vusal)
void	setup_parent_signals(void);
void	setup_child_signals(void);
void	setup_heredoc_signals(void);
int	    check_signal_received(void);
int     ft_pwd();
int	    ft_echo(char **args);
int 	ft_env(char **envp);
void	ft_free_split(char **arr);
int	    ft_exit(char **args);

#endif
