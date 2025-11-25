/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 14:43:48 by vhasanov          #+#    #+#             */
/*   Updated: 2025/11/25 12:25:43 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//GET VALUE FROM ENVP

char	*get_env_value(char **envp, const char *key)
{
	int		i;
	int		len;

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

// BUILD FULL PATH

static char	*build_full_path(char *dir, char *cmd)
{
	return (ft_strjoin_three(dir, "/", cmd));
}

//SEARCH PATH LIST

static char	*search_paths(char **paths, char *cmd)
{
	int		i;
	char	*full;

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

//RESOLVE COMMAND

char	*resolve_path(char **envp, char *cmd)
{
	char	*path_var;
	char	**paths;
	char	*result;
	int		i;

	/* If cmd contains '/', run it directly */
    
	if (strchr(cmd, '/')){
        if (access(cmd, X_OK) == 0)
		    return (strdup(cmd));
		return (NULL);
    }

	path_var = get_env_value(envp, "PATH");
	if (!path_var)
		return (NULL);

	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);

	result = search_paths(paths, cmd);

	//Free the split PATH array
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);

	return (result);
}

// It should check for the path if it is correct when user gave /sth
// ls -> strjointhree, / x strjointthree, 
