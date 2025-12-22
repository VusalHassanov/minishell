/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:58:36 by martin            #+#    #+#             */
/*   Updated: 2025/12/22 12:24:12 by mgunter          ###   ########.fr       */
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
		if (assign_redir(current[i], system) == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

static int	execute_redir_only(t_ast *node, t_shell *system)
{
	if (node->redir)
	{
		if (set_up_redirections(node, system) == ERROR)
		{
			system->exit_status = 1;
			return (1);
		}
	}
	system->exit_status = 0;
	return (0);
}

static int	execute_builtin_cmd(t_ast *node, char **current, t_shell *system)
{
	if (system->is_child == 0)
		ft_backup_fds(system->backup_fd);
	if (set_up_redirections(node, system) == ERROR)
	{
		if (system->is_child == 0)
			ft_reset_fds(system->backup_fd);
		system->exit_status = 1;
		return (1);
	}
	system->exit_status = execute_builtin(current, &(system->envp), system);
	if (system->is_child == 0)
		ft_reset_fds(system->backup_fd);
	return (system->exit_status);
}

int	execute_ast(t_ast *node, t_shell *system)
{
	char	**current;

	if (!node)
		return (0);
	if (node->node_type == TOKEN_PIPE)
	{
		create_pipe(node, system);
		return (system->exit_status);
	}
	handle_expansion(node->argv, system);
	current = find_first_argument(node->argv);
	if (!current || !current[0])
		return (execute_redir_only(node, system));
	if (is_builtin(current[0]))
		return (execute_builtin_cmd(node, current, system));
	system->exit_status = execute_external(node, system);
	return (system->exit_status);
}
