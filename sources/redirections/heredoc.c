/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:07:04 by martin            #+#    #+#             */
/*   Updated: 2025/12/14 12:05:41 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_delimiter_is_quoted(char *delimiter)
{
	int	len;

	len = ft_strlen(delimiter);
	if ((delimiter[0] == '\'' && delimiter[len] == '\'')
		|| (delimiter[0] == '\"' && delimiter[len] == '\"'))
		return (FALSE);
	return (TRUE);
}

int	ft_heredoc(int heredoc_fd, t_shell *system)
{
	char	buffer[1024];
	int		bytes_read;

	(void)system;
	if (heredoc_fd < 0)
	{
		return (ERROR);
	}
	if (dup2(heredoc_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 heredoc");
		close(heredoc_fd);
		return (ERROR);
	}
	close(heredoc_fd);
	return (SUCCESS);
}

// int	ft_heredoc(char *delimiter, t_shell *system)
// {
// 	int		pipe_fd[2];
// 	char	*line;
// 	int		expansion;
// 	char	*result;

// 	expansion = ft_delimiter_is_quoted(delimiter);
// 	if (pipe(pipe_fd) == -1)
// 	{
// 		perror("pipe");
// 		return (ERROR);
// 	}
// 	setup_heredoc_signals();
// 	while (1)
// 	{
// 		g_signal = 0;
// 		line = readline("> ");
// 		if (!line)
// 		{
// 				break ;
// 		}
// 		if (!line || !ft_strcmp(line, delimiter))
// 		{
// 			free(line);
// 			break ;
// 		}
// 		ft_putendl_fd(line, pipe_fd[1]);
// 		free(line);
// 	}
// 	setup_parent_signals();
// 	close(pipe_fd[1]);
// 	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
// 	{
// 		close(pipe_fd[0]);
// 		perror("dup2");
// 		return (ERROR);
// 	}
// 	close(pipe_fd[0]);
// 	return (SUCCESS);
// }

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