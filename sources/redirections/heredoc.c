/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:07:04 by martin            #+#    #+#             */
/*   Updated: 2025/12/15 13:18:51 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WRITE 0
#define READ 1

static int	set_up_heredoc_parsing(int *fd, int *expand_flag, char *delimitter,
		char **clean_delimitter)
{
	if (generate_temp_file(&fd[WRITE], &fd[READ]) == -1)
		return (ERROR);
	*expand_flag = ft_delimiter_is_quoted(delimitter);
	*clean_delimitter = remove_quotes(delimitter);
	g_signal = 0;
	setup_heredoc_signals();
	return (SUCCESS);
}

static int	heredoc_end_of_file(char *line, char *delimitter)
{
	if (!line || g_signal != 0)
	{
		if (!line && g_signal == 0)
			ft_putendl_fd("Warning: here-document delimited by end of file", 2);
		if (line)
			free(line);
		return (TRUE);
	}
	if (!ft_strcmp(line, delimitter))
	{
		free(line);
		return (TRUE);
	}
	return (FALSE);
}

int	get_input_heredoc_fd(char *delimitter, t_shell *system)
{
	char	*line;
	int		fd[2];
	int		expand_flag;
	char	*expanded;
	char	*clean_delimitter;

	if (set_up_heredoc_parsing(fd, &expand_flag, delimitter,
			&clean_delimitter) == ERROR)
		return (ERROR);
	while (1)
	{
		line = readline("heredoc>");
		if (g_signal != 0)
			return (heredoc_gsignal_error(line, fd[WRITE], fd[READ]));
		line = expand_if_needed(line, expand_flag, system);
		if (heredoc_end_of_file(line, clean_delimitter))
			break ;
		ft_putendl_fd(line, fd[WRITE]);
		free(line);
	}
	free(clean_delimitter);
	close(fd[WRITE]);
	setup_parent_signals();
	return (fd[READ]);
}

int	ft_heredoc(int heredoc_fd, t_shell *system)
{
	int	bytes_read;

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

// int	get_input_heredoc_fd(char *delimitter, t_shell *system)
// {
// 	char	*line;
// 	int		write_fd;
// 	int		read_fd;
// 	int		expand_flag;
// 	char	*expanded;

// 	if (generate_temp_file(&write_fd, &read_fd) == -1)
// 		return (-1);
// 	expand_flag = ft_delimiter_is_quoted(delimitter);
// 	delimitter = remove_quotes(delimitter);
// 	g_signal = 0;
// 	setup_heredoc_signals();
// 	while (1)
// 	{
// 		line = readline("heredoc>");
// 		if (g_signal != 0)
// 			return (heredoc_gsignal_error(line, write_fd, read_fd));
// 		line = expand_if_needed(line, expand_flag, system);
// 		if (!line || g_signal != 0)
// 		{
// 			if (!line && g_signal == 0)
// 				ft_putendl_fd("Warning: here-document delimited by end of file",
// 					2);
// 			if (line)
// 				free(line);
// 			break ;
// 		}
// 		if (!ft_strcmp(line, delimitter))
// 		{
// 			free(line);
// 			break ;
// 		}
// 		ft_putendl_fd(line, write_fd);
// 		free(line);
// 	}
// 	close(write_fd);
// 	setup_parent_signals();
// 	return (read_fd);
// }