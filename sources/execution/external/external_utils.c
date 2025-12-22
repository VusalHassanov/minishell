/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:25:17 by mgunter           #+#    #+#             */
/*   Updated: 2025/12/22 13:35:52 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

void	validate_node_and_system(t_ast *node, t_shell *system)
{
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
}

void	check_path_errors(char *cmd_path, char *cmd)
{
	struct stat	path_stat;

	if (stat(cmd_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		print_error_msg("minishell: ", cmd, ": is a directory\n");
		free(cmd_path);
		exit(126);
	}
	if (access(cmd_path, X_OK) != 0)
	{
		print_error_msg("minishell: ", cmd, ": ");
		perror(NULL);
		free(cmd_path);
		exit(126);
	}
}
