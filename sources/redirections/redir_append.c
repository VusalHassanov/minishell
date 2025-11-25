/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:19:02 by martin            #+#    #+#             */
/*   Updated: 2025/11/18 21:08:16 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_append(char *target)
{
	int	fd;

	fd = open(target, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(target);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

// int	main(int argc, char *argv[])
// {
// 	int fd_stdin;
// 	int fd_stdout;

// 	fd_stdin = dup(STDIN_FILENO);
// 	fd_stdout = dup(STDOUT_FILENO);
// 	ft_redir_append("text.txt");
// 	write(1, "Hello World\n", strlen("Hello World\n"));

// 	dup2(fd_stdin, STDIN_FILENO);
// 	dup2(fd_stdout, STDOUT_FILENO);
// 	return (0);
// }