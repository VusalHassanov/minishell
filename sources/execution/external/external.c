/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 14:01:27 by vhasanov          #+#    #+#             */
/*   Updated: 2025/12/22 13:34:40 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_parent_process(pid_t pid, t_ast *node, t_shell *system)
{
	int	status;

	if (pid == 0)
	{
		setup_child_signals();
		if (set_up_redirections(node, system) == ERROR)
			exit(EXIT_FAILURE);
		execute_child_process(node, system);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	setup_parent_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static pid_t	ft_fork_and_check(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork: ");
	}
	return (pid);
}

void	execute_child_process(t_ast *node, t_shell *system)
{
	char	*cmd_path;

	validate_node_and_system(node, system);
	cmd_path = resolve_path(system->envp, node->argv[0]);
	if (!cmd_path)
	{
		handle_command_not_found(node->argv[0]);
		exit(127);
	}
	check_path_errors(cmd_path, node->argv[0]);
	execve(cmd_path, node->argv, system->envp);
	handle_execve_error(node->argv[0], cmd_path);
	exit(126);
}

int	execute_external(t_ast *node, t_shell *system)
{
	pid_t	pid;

	if (system->is_child == 0)
	{
		pid = ft_fork_and_check();
		if (pid == -1)
			return (1);
		return (handle_parent_process(pid, node, system));
	}
	else
	{
		if (set_up_redirections(node, system) == ERROR)
			exit(EXIT_FAILURE);
		execute_child_process(node, system);
	}
	return (1);
}
