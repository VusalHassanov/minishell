/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:07:04 by martin            #+#    #+#             */
/*   Updated: 2025/12/12 12:44:30 by mgunter          ###   ########.fr       */
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
	int		pipe_fd[2];
	char	*line;
	int		expansion;
	char	*result;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		expansion = ft_delimiter_is_quoted(delimiter);
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return (ERROR);
		}
		setup_heredoc_signals();
		while (1)
		{
			// g_signal = 0;
			// rl_done = 0;
			line = readline("> ");
			// if (g_signal == SIGINT)
			// {
			// 	if (line)
			// 		free(line);
			// 	close(pipe_fd[0]);
			// 	close(pipe_fd[1]);
			// 	setup_parent_signals();
			// 	system->exit_status = 130;
			// 	return (ERROR);
			// }
			if (!line)
			{
				break ;
			}
			if (!ft_strcmp(line, delimiter))
			{
				free(line);
				break ;
			}
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
		exit (EXIT_SUCCESS);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
	}
		
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