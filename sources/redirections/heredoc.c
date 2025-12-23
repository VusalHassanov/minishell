/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:07:04 by martin            #+#    #+#             */
/*   Updated: 2025/12/23 18:26:02 by mgunter          ###   ########.fr       */
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
	setup_heredoc_signals();
	return (SUCCESS);
}

static int	heredoc_end_of_file(char *line, char *delimitter)
{
	if (!line)
	{
		if (!line)
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
	char	*clean_delimitter;

	if (set_up_heredoc_parsing(fd, &expand_flag, delimitter,
			&clean_delimitter) == ERROR)
		return (ERROR);
	while (1)
	{
		line = readline("> ");
		if (check_signal_received() != 0)
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
