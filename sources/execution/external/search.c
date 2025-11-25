/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 14:43:48 by vhasanov          #+#    #+#             */
/*   Updated: 2025/11/25 13:52:31 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* GET VALUE FROM ENVP */
char	*get_env_value(char **envp, const char *key)
{
	int		i;
	size_t	len;

	if (!envp || !key)
		return (NULL);
	len = strlen(key);
	i = 0;
	while (envp[i])
	{
		if (!strncmp(envp[i], key, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

/* BUILD FULL PATH */
char	*build_full_path(char *dir, char *cmd)
{
	char	*result;

	if (!dir || !cmd)
		return (NULL);
	result = ft_strjoin_three(dir, "/", cmd);
	return (result);
}

/* SEARCH PATH LIST */
char	*search_paths(char **paths, char *cmd)
{
	int		i;
	char	*full;

	if (!paths || !cmd)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full = build_full_path(paths[i], cmd);
		if (!full)
			return (NULL);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}


/* RESOLVE COMMAND */
char	*resolve_path(char **envp, char *cmd)
{
	char	*path_var;
	char	**paths;
	char	*result;

	if (!cmd || !envp)
		return (NULL);
	/* If cmd contains '/', treat it as a path */
	if (strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
				return (strdup(cmd));
			/* File exists but not executable */
			return (NULL);
		}
		/* File doesn't exist */
		return (NULL);
	}
	/* Search in PATH */
	path_var = get_env_value(envp, "PATH");
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);
	result = search_paths(paths, cmd);
	ft_free_split(paths);
	return (result);
}