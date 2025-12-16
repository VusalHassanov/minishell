/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:58:36 by martin            #+#    #+#             */
/*   Updated: 2025/12/16 20:15:47 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	assign_redir(t_redir *current, t_shell *system)
{
	if (!current->target)
		return (ERROR);
	if (current->type == TOKEN_REDIR_IN)
		return (ft_redir_in(current->target));
	else if (current->type == TOKEN_REDIR_APPEND)
		return (ft_redir_append(current->target));
	else if (current->type == TOKEN_REDIR_OUT)
		return (ft_redir_out(current->target));
	else if (current->type == TOKEN_HEREDOC)
		return (ft_heredoc(current->heredoc_fd, system));
	else
		return SUCCESS;
}

int	set_up_redirections(t_ast *node, t_shell *system)
{
	int		i;
	t_redir	**current;

	if (!node || !node->redir)
		return (SUCCESS);
	current = node->redir;
	i = 0;
	while (current[i])
	{
		/* ⭐ FIX #12: Check return value of each redirection */
		if (assign_redir(current[i], system) == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

// Find first non-empty argument
char **find_first_argument(char **argv)
{
	char **temp;
	int i;
	i = 0;
	while (argv && argv[i] && argv[i][0] == '\0')
	{
		i++;
	}
	if (argv && argv[i])
		return argv + i;
	return (NULL);
}

int	execute_ast(t_ast *node, t_shell *system)
{
	int		fd[2];
	char	**current;

	if (!node)
		return (0);
	
	if (node->node_type == TOKEN_PIPE)
	{
		create_pipe(node, system);
		return (system->exit_status);  // ⭐ FIX #14: Return the exit status
	}
	else
	{
		handle_expansion(node->argv, system);
		current = find_first_argument(node->argv);
		if (!current || !current[0])
		{
			system->exit_status = 0;
			return (0);
		}
		if (is_builtin(current[0]))
		{
			if (system->is_child == 0)
				ft_backup_fds(fd);
			
			/* ⭐ FIX #15: Handle redirection errors properly */
			if (set_up_redirections(node, system) == ERROR)
			{
				if (system->is_child == 0)
					ft_reset_fds(fd);
				system->exit_status = 1;
				return (1);
			}
			
			system->exit_status = execute_builtin(current, &(system->envp));
			if (system->is_child == 0)
				ft_reset_fds(fd);
			
			return (system->exit_status);  // ⭐ FIX #16: Return exit status
		}
		else
		{
			/* ⭐ FIX #17: Capture and return execute_external's exit status */
			system->exit_status = execute_external(node, system);
			return (system->exit_status);
		}
	}
}

// if argv[i][0] is empty, then it fails to call a function. 
// void	execute_ast(t_ast *node, t_shell *system)
// {
// 	int		fd[2];
// 	int		status;
// 	pid_t	pid;

// 	if (!node)
// 		return ;
// 	if (node->node_type == TOKEN_PIPE)
// 		create_pipe(node, system);
// 	else
// 	{
// 		handle_expansion(node->argv, system);
// 		if (is_builtin(node->argv[0]))
// 		{
// 			if (system->is_child == 0)
// 				ft_backup_fds(fd);
// 			if (set_up_redirections(node, system) == ERROR)
// 			{
// 				system->exit_status = 1;
// 				return ;
// 			}
// 			system->exit_status = execute_builtin(node->argv, &(system->envp));
// 			if (system->is_child == 0)
// 				ft_reset_fds(fd);
// 		}
// 		else
// 			system->exit_status = execute_external(node, system);
// 	}
// 	return ;
// }
