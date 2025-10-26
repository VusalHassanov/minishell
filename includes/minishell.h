#ifndef MINISHELL_H
# define MINISHELL_H
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
#include "lib_ft/libft.h"

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