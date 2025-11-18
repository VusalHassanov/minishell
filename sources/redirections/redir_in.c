/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:07:06 by martin            #+#    #+#             */
/*   Updated: 2025/11/18 21:20:48 by martin           ###   ########.fr       */
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
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

// int	main(int argc, char *argv[], char *env[])
// {
// 	int fd_stdin;
// 	int fd_stdout;
// 	char *args[] = {"text.txt", NULL};

// 	fd_stdin = dup(STDIN_FILENO);
// 	fd_stdout = dup(STDOUT_FILENO);
// 	ft_redir_in(args[0]);
// 	if (fork() == 0)
// 		execve("/usr/bin/cat", args, env);
// 	wait(NULL);
// 	dup2(fd_stdin, STDIN_FILENO);
// 	dup2(fd_stdout, STDOUT_FILENO);
// 	return (0);
// }