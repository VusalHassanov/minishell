/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:18:16 by vhasanov          #+#    #+#             */
/*   Updated: 2025/12/22 11:37:50 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**find_first_argument(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i] && argv[i][0] == '\0')
		i++;
	if (argv && argv[i])
		return (argv + i);
	return (NULL);
}

int	assign_redir(t_redir *current, t_shell *system)
{
	if (!current->target)
		return (ERROR);
	if (current->type == TOKEN_REDIR_IN)
		return (ft_redir_in(current->target));
	else if (current->type == TOKEN_REDIR_APPEND)
		return (ft_redir_append(current->target));
	else if (current->type == TOKEN_REDIR_OUT)
		return (ft_redir_out(current->target));
	else if (current->type == TOKEN_HEREDOC)
		return (ft_heredoc(current->heredoc_fd, system));
	else
		return (SUCCESS);
}

int	is_builtin(char *command)
{
	static const char	*builtin[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL
	};
	int					i;

	i = 0;
	while (builtin[i])
	{
		if (!ft_strcmp(builtin[i], command))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	execute_builtin(char **argv, char ***envp, t_shell *system)
{
	if (!argv || !argv[0])
		return (0);
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(argv));
	else if (ft_strcmp(argv[0], "env") == 0)
		return (ft_env(*envp));
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (ft_exit(argv, system));
	else if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(argv, envp));
	else if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(argv, envp));
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(argv, envp));
	return (0);
}
