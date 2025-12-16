/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:07:09 by martin            #+#    #+#             */
/*   Updated: 2025/12/15 15:13:03 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_out(char *target)
{
	int	fd;
	char *clean_target;

	clean_target = remove_quotes(target);
	if (!clean_target)
		return (ERROR);
	fd = open(clean_target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(clean_target);
		perror("open");
		return (ERROR);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
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
