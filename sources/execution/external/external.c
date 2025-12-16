/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 14:01:27 by vhasanov          #+#    #+#             */
/*   Updated: 2025/12/16 18:32:57 by vhasanov         ###   ########.fr       */
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

// int	handle_command_not_found(char *cmd, int error_code)
// {
// 	if (error_code == 1)
// 	{
// 		if (cmd[0] == '.' && cmd[1] == '/' || cmd[0] == '/')
// 		print_error_msg("minishell: ", cmd, ": No such file or directory\n");
// 	else
// 		print_error_msg("minishell: ", cmd, ": command not found\n");
// 	return (127);
// 	}
// 	if (error_code == 2)
// 	{
// 		print_error_msg("minishell: ", cmd, ": Is a directory\n");
// 		return (126);
// 	}
// }
void	handle_command_not_found(char *cmd)
{
	if (cmd[0] == '.' && cmd[1] == '/' || cmd[0] == '/')
		print_error_msg("minishell: ", cmd, ": No such file or directory\n");
	else
		print_error_msg("minishell: ", cmd, ": command not found\n");
}

static void	handle_execve_error(char *cmd, char *cmd_path)
{
	print_error_msg("minishell: ", cmd, ": ");
	perror(NULL);
	if (cmd_path)
		free(cmd_path);
}

int is_directory(const char *path)
{
    struct stat st;

    if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
        return (1);
    return (0);
}

void    execute_child_process(t_ast *node, t_shell *system)
{
    char            *cmd_path;
    struct stat     path_stat;
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

// void	execute_child_process(t_ast *node, t_shell *system)
// {
// 	char	*cmd_path;

// 	if (!node || !node->argv)
// 	{
// 		print_error_msg("minishell: internal error: ", "node or argv is NULL\n",
// 			NULL);
// 		exit(1);
// 	}
// 	if (!system || !system->envp)
// 	{
// 		print_error_msg("minishell: internal error: ",
// 			"system or envp is NULL\n", NULL);
// 		exit(1);
// 	}
// 	cmd_path = resolve_path(system->envp, node->argv[0]);
// 	if (!cmd_path)
// 	{
// 		exit(handle_command_not_found(node->argv[0], 1));
// 	}
// 	if (is_directory(cmd_path))
// 	{
// 		free(cmd_path);
// 		exit(handle_command_not_found(node->argv[0], 2));
// 	}
// 	execve(cmd_path, node->argv, system->envp);
// 	handle_execve_error(node->argv[0], cmd_path);
// 	exit(126);
// }

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
		
		/* ⭐ FIX #18: Properly handle ALL exit scenarios */
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));  // Normal exit
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));  // Killed by signal (Ctrl+C, etc.)
		return (1);
	}
	else
	{
		/* When we're already in a child process (pipe scenario) */
		if (set_up_redirections(node, system) == ERROR)
			exit(EXIT_FAILURE);
		execute_child_process(node, system);
		/* This will never be reached because execute_child_process calls exit() */
	}
	return (1);
}
