/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helper2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:29:30 by mgunter           #+#    #+#             */
/*   Updated: 2025/12/22 11:35:48 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_reset_fds(int *fd)
{
	if (!fd)
		return (ERROR);
	if (fd[0] != -1)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (ERROR);
		}
		close(fd[0]);
		fd[0] = -1;
	}
	if (fd[1] != -1)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (ERROR);
		}
		close(fd[1]);
		fd[1] = -1;
	}
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
