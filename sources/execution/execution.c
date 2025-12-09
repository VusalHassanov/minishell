/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:58:36 by martin            #+#    #+#             */
/*   Updated: 2025/12/09 21:46:24 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_up_redirections(t_ast *node, char **envp)
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
			ft_heredoc(current[i]->target, envp);
		i++;
	}
	return (1);
}

// int	execution_handler(t_ast *node, t_shell *system)
// {
// 	int		fd[2];
// 	char	*buffer;

// 	fd[0] = dup(STDIN_FILENO);
// 	fd[1] = dup(STDOUT_FILENO);
// 	if (!set_up_redirections(node, system->envp))
// 	{
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[1]);
// 		return (0);
// 	}
// 	handle_expansion(node->argv, system);
// 	if (is_builtin(node->argv[0]))
// 	{
// 		system->exit_status = execute_builtin(node->argv, &(system->envp));
// 	}
// 	else
// 	{
// 		system->exit_status = execute_external(node, system);
// 	}
// 	dup2(fd[0], STDIN_FILENO);
// 	close(fd[0]);
// 	dup2(fd[1], STDOUT_FILENO);
// 	close(fd[1]);
// 	return (1);
// }

int	execution_handler(t_ast *node, t_shell *system)
{
	int	fd[2];

	handle_expansion(node->argv, system);
	if (is_builtin(node->argv[0]))
	{
		if (system->is_child == 1)
		{
			set_up_redirections(node, system->envp);
			system->exit_status = execute_builtin(node->argv, &(system->envp));
		}
		else
		{
			ft_backup_fds(fd);
			set_up_redirections(node, system->envp);
			system->exit_status = execute_builtin(node->argv, &(system->envp));
			ft_reset_fds(fd);
		}
	}
	else
	{
		system->exit_status = execute_external(node, system);
	}
	return (1);
}

// int		fd[2];
// fd[0] = dup(STDIN_FILENO);
// fd[1] = dup(STDOUT_FILENO);
// if (!set_up_redirections(node, system->envp))
// {
// 	dup2(fd[0], STDIN_FILENO);
// 	close(fd[0]);
// 	dup2(fd[1], STDOUT_FILENO);
// 	close(fd[1]);
// 	return (0);
// }

// 	dup2(fd[0], STDIN_FILENO);
// close(fd[0]);
// dup2(fd[1], STDOUT_FILENO);
// close(fd[1]);

void	execute_ast(t_ast *node, t_shell *system)
{
	if (!node)
	{
		return ;
	}
	if (node->node_type == TOKEN_PIPE)
	{
		create_pipe(node, system);
	}
	else
	{
		if (!execution_handler(node, system))
		{
			// printf("oh no! execution handling error!\n");
		}
	}
}
