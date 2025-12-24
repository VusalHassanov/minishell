/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:25:15 by vhasanov          #+#    #+#             */
/*   Updated: 2025/12/22 12:13:26 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fds(t_shell *system)
{
	if (system->backup_fd[0] != -1)
	{
		close(system->backup_fd[0]);
		system->backup_fd[0] = -1;
	}
	if (system->backup_fd[1] != -1)
	{
		close(system->backup_fd[1]);
		system->backup_fd[1] = -1;
	}
}

int	ft_exit(char **argv, t_shell *system)
{
	int	status;

	ft_putstr_fd("exit\n", 1);
	close_fds(system);
	if (!argv[1])
		exit(0);
	if (!is_numeric(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	status = ft_atoi(argv[1]) % 256;
	exit(status);
}

// int	ft_exit(char **argv, t_shell *system)
// {
// 	int	status;

// 	ft_putstr_fd("exit\n", 1);
// 	if (system->backup_fd[0] != -1)
// 	{
// 		close(system->backup_fd[0]);
// 		system->backup_fd[0] = -1;
// 	}
// 	if (system->backup_fd[1] != -1)
// 	{
// 		close(system->backup_fd[1]);
// 		system->backup_fd[1] = -1;
// 	}
// 	if (!argv[1])
// 		exit(0);
// 	if (!is_numeric(argv[1]))
// 	{
// 		ft_putstr_fd("minishell: exit: ", 2);
// 		ft_putstr_fd(argv[1], 2);
// 		ft_putstr_fd(": numeric argument required\n", 2);
// 		exit(2);
// 	}
// 	if (argv[2])
// 	{
// 		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
// 		return (1);
// 	}
// 	status = ft_atoi(argv[1]) % 256;
// 	exit(status);
// }
