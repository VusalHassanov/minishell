/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:07:04 by martin            #+#    #+#             */
/*   Updated: 2025/12/10 22:16:21 by martin           ###   ########.fr       */
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
	char	*result;
	// int		interrupt;

	expansion = ft_delimiter_is_quoted(delimiter);
	pipe(pipe_fd);
	setup_heredoc_signals();
	// interrupt = 0;
	while (1)
	{
		line = readline(">");
		// interrupt = check_signal_received();
		// if (interrupt)
		// {
		// 	if (line)
		// 		free(line);
		// 	break ;
		// }
		// if (!line)
		// {
		// 	ft_putendl_fd("minishell: warning: here-document delimited by end-of-file",
		// 		2);
		// 	break ;
		// }
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
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
	// if (interrupt)
	// {
	// 	close(pipe_fd[0]);
	// 	system->exit_status = interrupt;
	// 	return (ERROR);
	// }
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