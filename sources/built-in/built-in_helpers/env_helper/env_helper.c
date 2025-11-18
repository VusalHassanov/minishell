/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:00:28 by vhasanov          #+#    #+#             */
/*   Updated: 2025/11/13 16:15:38 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// it will duplicate the env for future use like adding to env
char	**ft_envdup(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

// will give the envp path
char	*ft_getenv(char **envp, const char *name)
{
    int		i;
	size_t	len;
    
	if (!envp || !name)
		return (NULL);
	len = strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

// it will add a new envp to the env string
char **ft_env_add(char **envp, char *new_var)
{
    int i = 0;
    char **new_env;

    while (envp && envp[i])
        i++;

    new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
        return NULL;

    for (int j = 0; j < i; j++)
        new_env[j] = envp[j];

    new_env[i] = new_var;
    new_env[i + 1] = NULL;

    free(envp);
    return new_env;
}

// It will help to replace env if we found and existing one
int ft_env_replace(char **envp, const char *name, char *new_var)
{
    size_t len;
    int i;
    
    i = 0;
    len = ft_strlen(name);
    while (envp[i])
    {
        if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
        {
            free(envp[i]);
            envp[i] = new_var;
            return 1;
        }
        i++;
    }
    return 0;
}

// setting replace/add functions for environment
int ft_setenv(char ***envp, const char *name, const char *value)
{
    char *new_var;

    if (!envp || !name || !value)
        return 1;
    new_var = ft_strjoin_three(name, "=", value);
    if (!new_var)
        return 1;
    if (ft_env_replace(*envp, name, new_var))
        return 0;
    *envp = ft_env_add(*envp, new_var);
    if (!*envp){
        free(new_var);
        return 1;
    }
    return 0;
}

