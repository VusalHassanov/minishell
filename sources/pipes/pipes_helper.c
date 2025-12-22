/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:20:00 by mgunter           #+#    #+#             */
/*   Updated: 2025/12/22 12:23:17 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cleanup_pipe(int *pipe_fd, pid_t left, pid_t right,
		t_shell *system)
{
	int	left_status;
	int	right_status;

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(left, &left_status, 0);
	waitpid(right, &right_status, 0);
	setup_parent_signals();
	if (WIFEXITED(right_status))
		system->exit_status = WEXITSTATUS(right_status);
	else if (WIFSIGNALED(right_status))
		system->exit_status = 128 + WTERMSIG(right_status);
}

void	setup_pipe_redirect(int *pipe_fd, int child_type)
{
	if (child_type == LEFT)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2");
			exit(EXIT_FAILURE);
		}
	}
	else if (child_type == RIGHT)
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		{
			perror("minishell: dup2");
			exit(EXIT_FAILURE);
		}
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	ft_execute_pipe_child(t_ast *node, t_shell *system, int *pipe_fd,
		int child_type)
{
	int		exit_code;
	t_ast	*target;

	setup_child_signals();
	setup_pipe_redirect(pipe_fd, child_type);
	system->is_child = 1;
	if (child_type == LEFT)
		target = node->left;
	else
		target = node->right;
	exit_code = execute_ast(target, system);
	exit(exit_code);
}
