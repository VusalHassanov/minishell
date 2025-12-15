/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 16:13:46 by mgunter           #+#    #+#             */
/*   Updated: 2025/12/15 13:08:23 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_gsignal_error(char *line, int write_fd, int read_fd)
{
	if (line)
		free(line);
	close(write_fd);
	close(read_fd);
	setup_parent_signals();
	return (ERROR);
}

char	*expand_if_needed(char *line, int expand_flag, t_shell *system)
{
	char	*expanded;

	if (!line || !expand_flag)
		return (line);
	expanded = expand_string(line, system, expand_flag);
	if (expanded)
		free(line);
	return (expanded);
}

int	ft_delimiter_is_quoted(char *delimiter)
{
	int	len;

	len = ft_strlen(delimiter);
	if ((delimiter[0] == '\'' && delimiter[len - 1] == '\'')
		|| (delimiter[0] == '\"' && delimiter[len - 1] == '\"'))
		return (FALSE);
	return (TRUE);
}
