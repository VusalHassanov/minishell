/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:58:36 by martin            #+#    #+#             */
/*   Updated: 2025/12/16 20:00:10 by vhasanov         ###   ########.fr       */
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
		assign_redir(current[i], system);
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

void	execute_ast(t_ast *node, t_shell *system)
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
			if (set_up_redirections(node, system) == ERROR)
				return ;
			system->exit_status = execute_builtin(node->argv, &(system->envp));
			if (system->is_child == 0)
				ft_reset_fds(fd);
			
			return (system->exit_status);  // ⭐ FIX #16: Return exit status
		}
		else
			execute_external(node, system);
	}
}
