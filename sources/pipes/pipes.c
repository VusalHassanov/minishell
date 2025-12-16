/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:20:35 by martin            #+#    #+#             */
/*   Updated: 2025/12/16 15:40:38 by vhasanov         ###   ########.fr       */
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
	int	left_status;   // ⭐ FIX: Separate variable for left child
	int	right_status;  // ⭐ FIX: Separate variable for right child

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	
	/* ⭐ FIX #3: Wait for both children and capture BOTH statuses */
	waitpid(left, &left_status, 0);    // Don't lose this status!
	waitpid(right, &right_status, 0);  // Get this status too!
	
	setup_parent_signals();
	
	/* 
	 * ⭐ FIX #4: Use the RIGHTMOST command's exit status (bash behavior)
	 * In a pipe like "ls | grep", we want grep's exit status, not ls's
	 */
	if (WIFEXITED(right_status))
		system->exit_status = WEXITSTATUS(right_status);
	else if (WIFSIGNALED(right_status))
		system->exit_status = 128 + WTERMSIG(right_status);  // ⭐ FIX: Handle signals
}


static void	ft_execute_pipe_child(t_ast *node, t_shell *system, int *pipe_fd,
		int child_type)
{
	int	exit_code;  // ⭐ FIX #5: Added variable to capture exit code
	
	setup_child_signals();
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
	system->is_child = 1;
	
	/* ⭐ FIX #6: Capture the return value from execute_ast */
	if (child_type == LEFT)
		exit_code = execute_ast(node->left, system);
	else
		exit_code = execute_ast(node->right, system);
	
	/* ⭐ FIX #7: Exit with the actual exit code, not always EXIT_SUCCESS */
	exit(exit_code);
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
		system->exit_status = 1;  // ⭐ FIX #8: Set exit status on error
		return ;
	}
	left = ft_fork_and_check(pipe_fd);
	if (left < 0)
	{
		system->exit_status = 1;  // ⭐ FIX #9: Set exit status on fork error
		return ;
	}
	if (left == 0)
		ft_execute_pipe_child(node, system, pipe_fd, LEFT);
	
	right = ft_fork_and_check(pipe_fd);
	if (right < 0)
	{
		waitpid(left, &status, 0);
		system->exit_status = 1;  // ⭐ FIX #10: Set exit status on fork error
		return ;
	}
	if (right == 0)
		ft_execute_pipe_child(node, system, pipe_fd, RIGHT);
	
	/* ⭐ FIX #11: Pass system to ft_cleanup_pipe so it can update exit_status */
	ft_cleanup_pipe(pipe_fd, left, right, system);
}
