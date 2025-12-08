/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:07:04 by martin            #+#    #+#             */
/*   Updated: 2025/11/30 16:06:51 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_delimiter_is_quoted(char *delimiter)
{
	int	len;

	len = ft_strlen(delimiter);
	return ((delimiter[0] == '\'' && delimiter[len] == '\'')
		|| (delimiter[0] == '\"' && delimiter[len] == '\"'));
}

int	ft_heredoc(char *delimiter, char **envp)
{
	int		pipe_fd[2] = {0};
	char	*line;
	int		expansion;

	expansion = ft_delimiter_is_quoted(delimiter);
	pipe(pipe_fd);
	while (1)
	{
		line = readline(">");
		if (!line || !ft_strcmp(line, delimiter))
			break ;
		if (expansion == 1)
		{
			// line = expand_string(line, envp);
		}
		ft_putendl_fd(line, pipe_fd[1]);
		free(line);
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		close(pipe_fd[0]);
		perror("dup2");
		return (ERROR);
	}
	close(pipe_fd[0]);
	return (SUCCESS);
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