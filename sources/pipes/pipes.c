/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:20:35 by martin            #+#    #+#             */
/*   Updated: 2025/11/18 15:57:40 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>


// pipe_fd[0] read end
// pipe_fd[1] write end
void	create_pipe(t_ast *node, int depth)
{
	int	pipe_fd[2] = {0};
	int	left;
	int	right;

	pipe(pipe_fd);
	left = fork();
	if (left == 0)
	{
		setup_child_signals();
		dup2(pipe_fd[1], 1);
		close(pipe_fd[0]);
		execute_ast(node->left, ++depth);
		close(pipe_fd[1]);
		exit(EXIT_SUCCESS);
	}
	right = fork();
	if (right == 0)
	{
		setup_child_signals();
		dup2(pipe_fd[0], 0);
		close(pipe_fd[1]);
		execute_ast(node->right, ++depth);
		close(pipe_fd[0]);
		exit(EXIT_SUCCESS);
	}
	waitpid(left, 0, 0);
	waitpid(right, 0, 0);
	return ;
}

// int	main(void)
// {
// 	t_ast	node4_left = {TOKEN_COMMAND, NULL, NULL, NULL, NULL};
// 	t_ast	node4_right = {TOKEN_COMMAND, NULL, NULL, NULL, NULL};
// 	t_ast	node3_right = {TOKEN_PIPE, NULL, NULL, &node4_left, &node4_right};
// 	t_ast	node3_left = {TOKEN_COMMAND, NULL, NULL, NULL, NULL};
// 	t_ast	node2 = {TOKEN_PIPE, NULL, NULL, &node3_left, &node3_right};
// 	t_ast	node1 = {TOKEN_PIPE, NULL, NULL, &node2, NULL};

// 	execute_ast(&node1, 1);
// 	return (0);
// }
