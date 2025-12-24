/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:35:07 by mgunter           #+#    #+#             */
/*   Updated: 2025/12/23 16:01:15 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_msg(const char *prefix, const char *msg, const char *suffix)
{
	if (prefix)
		write(STDERR_FILENO, prefix, ft_strlen(prefix));
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	if (suffix)
		write(STDERR_FILENO, suffix, ft_strlen(suffix));
}

void	handle_command_not_found(char *cmd)
{
	if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/')
		print_error_msg("minishell: ", cmd, ": No such file or directory\n");
	else
		print_error_msg("minishell: ", cmd, ": command not found\n");
}

void	handle_execve_error(char *cmd, char *cmd_path)
{
	print_error_msg("minishell: ", cmd, ": ");
	perror(NULL);
	if (cmd_path)
		free(cmd_path);
}
