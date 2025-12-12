/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:58:36 by martin            #+#    #+#             */
/*   Updated: 2025/12/12 11:58:16 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_up_redirections(t_ast *node, t_shell *system)
{
	int		i;
	t_redir	**current;

	if (!node || !node->redir)
		return (1);
	current = node->redir;
	i = 0;
	while (current[i])
	{
		if (!current[i]->target)
			return (0);
		if (current[i]->type == TOKEN_REDIR_IN)
			ft_redir_in(current[i]->target);
		else if (current[i]->type == TOKEN_REDIR_APPEND)
			ft_redir_append(current[i]->target);
		else if (current[i]->type == TOKEN_REDIR_OUT)
			ft_redir_out(current[i]->target);
		else if (current[i]->type == TOKEN_HEREDOC)
		{
			if(ft_heredoc(current[i]->target, system) == FAILURE)
			 return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

void	execute_ast(t_ast *node, t_shell *system)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	if (!node)
		return ;
	if (node->node_type == TOKEN_PIPE)
		create_pipe(node, system);
	else
	{
		handle_expansion(node->argv, system);
		if (is_builtin(node->argv[0]))
		{
			if (system->is_child == 0)
				ft_backup_fds(fd);
			if(set_up_redirections(node, system)== ERROR)
				return ;
			system->exit_status = execute_builtin(node->argv, &(system->envp));
			if (system->is_child == 0)
				ft_reset_fds(fd);
		}
		else
			execute_external(node, system);
	}
}

// int	execution_handler(t_ast *node, t_shell *system)
// {
// 	int		fd[2];
// 	int		status;
// 	pid_t	pid;

// 	handle_expansion(node->argv, system);
// 	if (is_builtin(node->argv[0]))
// 	{
// 		if (system->is_child == 0)
// 			ft_backup_fds(fd);
// 		set_up_redirections(node, system);
// 		system->exit_status = execute_builtin(node->argv, &(system->envp));
// 		if (system->is_child == 0)
// 			ft_reset_fds(fd);
// 		return (SUCCESS);
// 	}
// 	else
// 		execute_external(node, system);
// 	return (FAILURE);
// }

// void	execute_ast(t_ast *node, t_shell *system)
// {
// 	if (!node)
// 		return ;
// 	if (node->node_type == TOKEN_PIPE)
// 		create_pipe(node, system);
// 	else
// 	{
// 		if (execution_handler(node, system) == FAILURE)
// 		{
// 			ft_putendl_fd("Execution error", 2);
// 		}
// 	}
// }

// int	execution_handler(t_ast *node, t_shell *system)
// {
// 	int	fd[2];
// 	int status;
// 	pid_t pid;

// 	handle_expansion(node->argv, system);
// 	if (is_builtin(node->argv[0]))
// 	{
// 		if (system->is_child == 0)
// 			ft_backup_fds(fd);
// 		set_up_redirections(node, system);
// 		system->exit_status = execute_builtin(node->argv, &(system->envp));
// 		if(system->is_child == 0)
// 			ft_reset_fds(fd);
// 		}
// 	else
// 	{
// 		if (system->is_child == 1)
// 		{
// 			system->exit_status = execute_external(node, system);
// 		}
// 		else
// 			pid = fork();
// 			if (pid < 0)
// 			{
// 			perror("minishell: fork: ");
// 			return (FAILURE);
// 			}
// 			if (pid == 0)
// 			{
// 				setup_child_signals();
// 				system->exit_status = execute_external(node, system);
// 			}
// 			else
// 				wait(&status);
// 	}
// 	return (FAILURE);
// }
