/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:07:04 by martin            #+#    #+#             */
/*   Updated: 2025/12/10 16:32:51 by mgunter          ###   ########.fr       */
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

int	ft_heredoc(char *delimiter, t_shell *system)
{
	int		pipe_fd[2] = {0};
	char	*line;
	int		expansion;
	char 	*result;

	expansion = ft_delimiter_is_quoted(delimiter);
	pipe(pipe_fd);
	setup_heredoc_signals();
	while (1)
	{
		line = readline(">");
		if (!line || !ft_strcmp(line, delimiter))
			break ;
		if (expansion == TRUE)
		{
			result = expand_string(line, system);
			ft_putendl_fd(result, pipe_fd[1]);
			free(result);
		}
		else
			ft_putendl_fd(line, pipe_fd[1]);
		free(line);
	}
	setup_parent_signals();
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