/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:07:04 by martin            #+#    #+#             */
/*   Updated: 2025/11/25 13:51:37 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static char	*expand_string(char *line, char **envp)
{
	int		i;
	int		variable_len;
	char	*result;
	char	*variable_name;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			while (ft_isprint)
			{
				variable_len++;
				i++;
			}
			
		}
			
	}
}

static int	ft_delimiter_is_quoted(char *delimiter)
{
	int	len;

	len = ft_strlen(delimiter);
	return ((delimiter[0] == '\'' && delimiter[len] == '\'')
		|| (delimiter[0] == '\"' && delimiter[len] == '\"'));
}

// takes also envp
int	ft_heredoc(char *delimiter)
{
	int		pipe_fd[2] = {0};
	char	*line;
	int		fd;
	int		expansion;

	expansion = 0;
	expansion = ft_delimiter_is_quoted(delimiter);
	pipe(pipe_fd);
	while (1)
	{
		line = readline(">");
		if (!line || !ft_strcmp(line, delimiter))
			break ;
		if (expansion == 0)
		{
			// line = expand_heredoc_string(line);
		}
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