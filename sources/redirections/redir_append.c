/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:19:02 by martin            #+#    #+#             */
/*   Updated: 2025/12/15 15:12:24 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_append(char *target)
{
	int		fd;
	char	*clean_target;

	clean_target = remove_quotes(target);
	if (!clean_target)
		return (ERROR);
	fd = open(clean_target, O_WRONLY | O_APPEND | O_CREAT, 0644);
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

// int	ft_redir_append(char *target)
// {
// 	int	fd;

// 	fd = open(target, O_WRONLY | O_APPEND | O_CREAT, 0644);
// 	if (fd == -1)
// 	{
// 		perror(target);
// 		return (ERROR);
// 	}
// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 	{
// 		perror("dup2");
// 		close(fd);
// 		return (ERROR);
// 	}
// 	close(fd);
// 	return (SUCCESS);
// }
