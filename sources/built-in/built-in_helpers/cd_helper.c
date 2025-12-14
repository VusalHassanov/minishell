/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:01:41 by vhasanov          #+#    #+#             */
/*   Updated: 2025/12/14 20:58:28 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_tilde(char *path, char **envp)
{
	char	*home;
	char	*result;

	// If path doesn't start with ~, return as is
	if (!path || path[0] != '~')
		return (path);
	home = ft_getenv(envp, "HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (NULL);
	}
	// If just ~, return HOME
	if (path[1] == '\0')
		return (home);
	// If ~/something, join HOME with the rest of the path
	if (path[1] == '/')
	{
		result = ft_strjoin(home, path + 1);
		return (result);
	}
	return (path);
}

char	*cd_get_target(char **argv, char **envp)
{
	char	*home;
	char	*target;

	if (argv[1] == NULL)
	{
		home = ft_getenv(envp, "HOME");
		if (!home)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (NULL);
		}
		return (home);
	}
	target = expand_tilde(argv[1], envp);
	return (target);
}
