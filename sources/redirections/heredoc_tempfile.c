/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tempfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:08:32 by mgunter           #+#    #+#             */
/*   Updated: 2025/12/15 13:49:19 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*generate_temp_filename(void)
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
		return (ERROR);
	*write_fd = open(temp_filename, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (*write_fd == ERROR)
	{
		perror("open");
		free(temp_filename);
		return (ERROR);
	}
	*read_fd = open(temp_filename, O_RDONLY, 0600);
	if (*read_fd == ERROR)
	{
		perror("open for reading");
		close(*write_fd);
		unlink(temp_filename);
		free(temp_filename);
		return (ERROR);
	}
	unlink(temp_filename);
	free(temp_filename);
	return (SUCCESS);
}
