/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:20:35 by martin            #+#    #+#             */
/*   Updated: 2025/12/16 15:47:28 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	ft_fork_and_check(int *pipe_fd)
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

static void	ft_cleanup_pipe(int *pipe_fd, pid_t left, pid_t right, t_shell *system)
{
	int	status;
	char temp[8];
	char *exit_code;

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(left, &status, 0);
	waitpid(right, &status, 0);
}

static void	ft_execute_pipe_child(t_ast *node, t_shell *system, int *pipe_fd,
		int child_type)
{
	setup_child_signals();
	if (child_type == LEFT)
	{
		if (dup2(pipe_fd[1], 1) == -1)
		{
			perror("minishell: dup2");
			exit(EXIT_FAILURE);
		}
	}
	else if (child_type == RIGHT)
	{
		if (dup2(pipe_fd[0], 0) == -1)
		{
			perror("minishell: dup2");
			exit(EXIT_FAILURE);
		}
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	system->is_child = 1;
	if (child_type == LEFT)
		execute_ast(node->left, system);
	else if (child_type == RIGHT)
		execute_ast(node->right, system);
	exit(EXIT_SUCCESS);
}

void	create_pipe(t_ast *node, t_shell *system)
{
	int		pipe_fd[2];
	pid_t	left;
	pid_t	right;
	int		status;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return ;
	}
	left = ft_fork_and_check(pipe_fd);
	if (left < 0)
		return ;
	if (left == 0)
		ft_execute_pipe_child(node, system, pipe_fd, LEFT);
	right = ft_fork_and_check(pipe_fd);
	if (right < 0)
	{
		waitpid(left, &status, 0);
		return ;
	}
	if (right == 0)
		ft_execute_pipe_child(node, system, pipe_fd, RIGHT);
	ft_cleanup_pipe(pipe_fd, left, right, system);
}
