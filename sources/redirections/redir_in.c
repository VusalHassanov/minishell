/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:07:06 by martin            #+#    #+#             */
/*   Updated: 2025/12/15 15:12:57 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_in(char *target)
{
	int	fd;
	char *clean_target;

	clean_target = remove_quotes(target);
	if (!clean_target)
		return (ERROR);
	fd = open(clean_target, O_RDONLY);
	if (fd == -1)
	{
		free(clean_target);
		perror("open");
		return (ERROR);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		free(clean_target);
		perror("dup2");
		close(fd);
		return (ERROR);
	}
	free(clean_target);
	close(fd);
	return (SUCCESS);
}
