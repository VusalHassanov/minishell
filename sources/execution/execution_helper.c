/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:18:16 by vhasanov          #+#    #+#             */
/*   Updated: 2025/12/09 21:44:00 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	int		i;
	char	*builtin[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit",
			NULL};

	i = 0;
	while (builtin[i])
	{
		if (!ft_strcmp(builtin[i], command))
			return (1);
		i++;
	}
	return (0);
}

int	ft_reset_fds(int *fd)
{
	if (!fd)
		return (ERROR);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (ERROR);
	}
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (ERROR);
	}
	close(fd[1]);
	return (SUCCESS);
}

int	ft_backup_fds(int *fd)
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (fd[0] == -1 || fd[1] == -1)
	{
		perror("dup fail");
		return (ERROR);
	}
	else
		return (SUCCESS);
}

int	execute_builtin(char **argv, char ***envp)
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
		return (ft_exit(argv));
	else if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(argv, envp));
	else if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(argv, envp));
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(argv, envp));
	return (0);
}
