/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 14:01:27 by vhasanov          #+#    #+#             */
/*   Updated: 2025/12/16 18:30:28 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	print_error_msg(const char *prefix, const char *msg, const char *suffix)
{
	if (prefix)
		write(STDERR_FILENO, prefix, ft_strlen(prefix));
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	if (suffix)
		write(STDERR_FILENO, suffix, ft_strlen(suffix));
}

/* Optional: count similar commands and display suggestion */
/* Pass envp if implementing: count_similar_in_path(envp, cmd) */
void	handle_command_not_found(char *cmd)
{
	print_error_msg("minishell: ", cmd, ": command not found\n");
}

static void	handle_execve_error(char *cmd, char *cmd_path)
{
	print_error_msg("minishell: ", cmd, ": ");
	perror(NULL);
	if (cmd_path)
		free(cmd_path);
}

void	execute_child_process(t_ast *node, t_shell *system)
{
	char			*cmd_path;
	struct stat		path_stat;

	if (!node || !node->argv)
	{
		print_error_msg("minishell: internal error: ", "node or argv is NULL\n",
			NULL);
		exit(1);
	}
	if (!system || !system->envp)
	{
		print_error_msg("minishell: internal error: ",
			"system or envp is NULL\n", NULL);
		exit(1);
	}
	cmd_path = resolve_path(system->envp, node->argv[0]);
	if (!cmd_path)
	{
		handle_command_not_found(node->argv[0]);
		exit(127);
	}
	if (stat(cmd_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		print_error_msg("minishell: ", node->argv[0], ": is a directory\n");
		free(cmd_path);
		exit(126);
	}
	execve(cmd_path, node->argv, system->envp);
	handle_execve_error(node->argv[0], cmd_path);
	exit(126);
}

int	execute_external(t_ast *node, t_shell *system)
{
	int		status;
	pid_t	pid;

	if (system->is_child == 0)
	{
		pid = ft_fork_and_check();
		if (pid == -1)
			return (1);
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
		return (1);
	}
	else
	{
		if (set_up_redirections(node, system) == ERROR)
			exit(EXIT_FAILURE);
		execute_child_process(node, system);
	}
	return (1);
}
