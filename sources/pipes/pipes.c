/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:20:35 by martin            #+#    #+#             */
/*   Updated: 2025/12/22 12:22:08 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	ft_fork_and_check_pipe(int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork: ");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	return (pid);
}

int	fork_left_child(t_ast *node, t_shell *system, int *pipe_fd)
{
	pid_t	pid;

	pid = ft_fork_and_check_pipe(pipe_fd);
	if (pid < 0)
		return (-1);
	if (pid == 0)
		ft_execute_pipe_child(node, system, pipe_fd, LEFT);
	return (pid);
}

int	fork_right_child(t_ast *node, t_shell *system, int *pipe_fd,
		pid_t left)
{
	pid_t	pid;
	int		status;

	pid = ft_fork_and_check_pipe(pipe_fd);
	if (pid < 0)
	{
		waitpid(left, &status, 0);
		return (-1);
	}
	if (pid == 0)
		ft_execute_pipe_child(node, system, pipe_fd, RIGHT);
	return (pid);
}

void	create_pipe(t_ast *node, t_shell *system)
{
	int		pipe_fd[2];
	pid_t	left;
	pid_t	right;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		system->exit_status = 1;
		return ;
	}
	left = fork_left_child(node, system, pipe_fd);
	if (left < 0)
	{
		system->exit_status = 1;
		return ;
	}
	right = fork_right_child(node, system, pipe_fd, left);
	if (right < 0)
	{
		system->exit_status = 1;
		return ;
	}
	ft_cleanup_pipe(pipe_fd, left, right, system);
}
