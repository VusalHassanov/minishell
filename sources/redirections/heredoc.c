/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:07:04 by martin            #+#    #+#             */
/*   Updated: 2025/12/15 12:00:03 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WRITE 0
#define READ 1

static int	ft_delimiter_is_quoted(char *delimiter)
{
	int	len;

	len = ft_strlen(delimiter);
	if ((delimiter[0] == '\'' && delimiter[len] == '\'')
		|| (delimiter[0] == '\"' && delimiter[len] == '\"'))
		return (FALSE);
	return (TRUE);
}

char	*generate_temp_filename(void)
{
	static int	counter = 0;
	char		*counter_str;
	char		*filename;

	counter_str = ft_itoa(counter++);
	if (!counter_str)
		return (NULL);
	filename = ft_strjoin("/tmp/minishell_heredoc_", counter_str);
	free(counter_str);
	return (filename);
}

int	generate_temp_file(int *write_fd, int *read_fd)
{
	char	*temp_filename;

	temp_filename = generate_temp_filename();
	if (!temp_filename)
		return (-1);
	*write_fd = open(temp_filename, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (*write_fd == -1)
	{
		perror("open");
		free(temp_filename);
		return (-1);
	}
	*read_fd = open(temp_filename, O_RDONLY, 0600);
	if (*read_fd == -1)
	{
		perror("open for reading");
		close(*write_fd);
		unlink(temp_filename);
		free(temp_filename);
		return (-1);
	}
	unlink(temp_filename);
	free(temp_filename);
	return (0);
}

int	set_up_heredoc_parsing(int *fd, int *expand_flag, char **delimitter)
{
	if (generate_temp_file(&fd[0], &fd[1]) == -1)
		return (ERROR);
	*expand_flag = ft_delimiter_is_quoted(*delimitter);
	*delimitter = remove_quotes(*delimitter);
	g_signal = 0;
	setup_heredoc_signals();
	return (SUCCESS);
}

int	heredoc_end_of_file(char *line, char *delimitter)
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
		return TRUE;
	}
	return (FALSE);
}

// fd[0] write temp file
// fd[1] read temp file
int	get_input_heredoc_fd(char *delimitter, t_shell *system)
{
	char	*line;
	int		fd[2];
	int		expand_flag;
	char	*expanded;

	if (set_up_heredoc_parsing(fd, &expand_flag, &delimitter) == ERROR)
		return (ERROR);
	while (1)
	{
		line = readline("heredoc>");
		if (g_signal != 0)
			return (heredoc_gsignal_error(line, fd[0], fd[1]));
		line = expand_if_needed(line, expand_flag, system);
		if (heredoc_end_of_file(line, delimitter))
			break ;
		ft_putendl_fd(line, fd[0]);
		free(line);
	}
	close(fd[0]);
	setup_parent_signals();
	return (fd[1]);
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