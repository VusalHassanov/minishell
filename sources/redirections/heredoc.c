/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:07:04 by martin            #+#    #+#             */
/*   Updated: 2025/11/23 16:56:27 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

// delimitter is the delimitter
int	ft_heredoc(char *delimiter)
{
	int		pipe_fd[2] = {0};
	char	*line;
	int		fd;

	pipe(pipe_fd);
	while (1)
	{
		line = readline(">");
		if (!line || !ft_strcmp(line, delimiter))
			break ;
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
}

// int	main(void)
// {
// 	char	*args[] = {"EOF", NULL};

// 	ft_heredoc(args[0]);
// 	if (fork() == 0)
// 	{
// 		execve("/usr/bin/wc", args, NULL);
// 	}
// 	wait(NULL);
// 	return (0);
// }