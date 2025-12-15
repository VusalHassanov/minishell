/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:07:06 by martin            #+#    #+#             */
/*   Updated: 2025/12/15 11:59:32 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_in(char *target)
{
	int	fd;

	fd = open(target, O_RDONLY);
	if (fd == -1)
	{
		perror(target);
		return (ERROR);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (ERROR);
	}
	close(fd);
	return (SUCCESS);
}
