/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:58:36 by martin            #+#    #+#             */
/*   Updated: 2025/12/16 19:40:09 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// int	set_up_redirections(t_ast *node, t_shell *system)
// {
// 	int		i;
// 	t_redir	**current;
// 	if (!node || !node->redir)
// 		return (1);
// 	current = node->redir;
// 	i = 0;
// 	while (current[i])
// 	{
// 		if (!current[i]->target)
// 			return (0);
// 		if (current[i]->type == TOKEN_REDIR_IN)
// 			return (ft_redir_in(current[i]->target));
// 		else if (current[i]->type == TOKEN_REDIR_APPEND)
// 			return(ft_redir_append(current[i]->target));
// 		else if (current[i]->type == TOKEN_REDIR_OUT)
// 			return(ft_redir_out(current[i]->target));
// 		else if (current[i]->type == TOKEN_HEREDOC)
// 			return (ft_heredoc(current[i]->heredoc_fd, system));
// 		i++;
// 	}
// 	return (SUCCESS);
// }

int	execute_ast(t_ast *node, t_shell *system)
{
	int		fd[2];

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
		if (is_builtin(node->argv[0]))
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
			
			system->exit_status = execute_builtin(node->argv, &(system->envp));
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
