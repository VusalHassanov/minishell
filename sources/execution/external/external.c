/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 14:01:27 by vhasanov          #+#    #+#             */
/*   Updated: 2025/11/30 17:25:36 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int execute_external(t_ast *node)
// {
//     pid_t pid;
//     int status;

//     pid = fork();
//     if (pid < 0)
//     {
//         perror("fork");
//         return (1);
//     }
//     if (pid == 0)
//     {
//         // if (!set_up_redirections(node))
//         //     exit(EXIT_FAILURE);
//         execvp(node->argv[0], node->argv);
//         perror("execvp");
//         exit(EXIT_FAILURE);
//     }
//     waitpid(pid, &status, 0);
//     if (WIFEXITED(status))
//         return (WEXITSTATUS(status));
//     return (1);
// }

// int	execute_external(t_ast *node, char **envp, int is_child, int *backup_fds)
// {
// 	pid_t	pid;
// 	int		status;

// 	char	*path;
// 	path = resolve_path(envp, node->argv[0]);
// 	if (is_child == 1)
// 	{
// 		execvp(path, node->argv);
// 		perror("execvp");
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		pid = fork();
// 		if (pid < 0)
// 		{
// 			perror("fork");
// 			return (1);
// 		}
// 		if (pid == 0)
// 		{
// 			if (backup_fds)
// 			{
// 				close(backup_fds[0]);
// 				close(backup_fds[1]);
// 			}
// 			execvp(node->argv[0], node->argv);
// 			perror("execvp");
// 			exit(EXIT_FAILURE);
// 		}
// 		waitpid(pid, &status, 0);
// 		if (WIFEXITED(status))
// 			return (WEXITSTATUS(status));
// 	}
// 	return (1);
// }


int	execute_external(t_ast *node, char **envp, int is_child, int *backup_fds)
{
	char	*path;

	if (is_child != 1)
	{
		ft_putstr_fd("Error: execute_external called in parent process\n", 2);
		return (ERROR);
	}
	if (backup_fds)
	{
		close(backup_fds[0]);
		close(backup_fds[1]);
	}
	path = resolve_path(envp, node->argv[0]);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(node->argv[0], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	execvp(path, node->argv);
	perror("execvp");
	free(path);
	exit(EXIT_FAILURE);
}
