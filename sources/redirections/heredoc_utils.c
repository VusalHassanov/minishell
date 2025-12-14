/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 16:13:46 by mgunter           #+#    #+#             */
/*   Updated: 2025/12/14 18:06:11 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_string2(char *str, t_shell *system)
{
	char	*result;
	char	*final;
	int		i;

	i = 0;
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	while (result[i])
	{
		if (result[i] == '$')
			result = expand_variable(result, &i, system);
		else
			i++;
	}
	return (result);
}

int heredoc_gsignal_error(char *line, int write_fd, int read_fd)
{
    if(line)
        free(line);
    close(write_fd);
	close(read_fd);
	setup_parent_signals();
	return (ERROR);
}

char *expand_if_needed(char *line, int expand_flag, t_shell *system)
{
    char *expanded;

    if (!line || !expand_flag)
        return (line);
    expanded = expand_string2(line, system);
	if (expanded)
		free(line);
    return expanded;
}


