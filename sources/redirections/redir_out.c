/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:07:09 by martin            #+#    #+#             */
/*   Updated: 2025/11/25 19:07:05 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_out(char *target)
{
	int	fd;

	fd = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(target);
		return (ERROR);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (ERROR);
	}
	close(fd);
	return (SUCCESS);
}

// int	main(int argc, char *argv[])
// {
// 	int fd_stdin;
// 	int fd_stdout;

// 	fd_stdin = dup(STDIN_FILENO);
// 	fd_stdout = dup(STDOUT_FILENO);
// 	ft_redir_ot("text.txt");
// 	write(1, "Hello World", strlen("Hello World"));

// 	dup2(fd_stdin, STDIN_FILENO);
// 	dup2(fd_stdout, STDOUT_FILENO);
// 	return (0);
// }
