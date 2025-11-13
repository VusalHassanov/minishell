/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:49:02 by vhasanov          #+#    #+#             */
/*   Updated: 2025/11/13 16:06:48 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//update environment for old and new paths
void update_env(char ***envp, char *oldpwd)
{
    char *newpwd = getcwd(NULL, 0);
    if (!newpwd)
        return (perror("cd"), void());

    ft_setenv(envp, "OLDPWD", oldpwd);
    ft_setenv(envp, "PWD", newpwd);
    free(newpwd);
}

// to remove an env variable from environment
char **envp_remove(char **envp, const char *name)
{
    int i;
    int j;
    size_t len;

    if (!envp || !name)
        return envp;
    len = ft_strlen(name);
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
        {
            free(envp[i]);
            j = i;
            while (envp[j + 1])
            {
                envp[j] = envp[j + 1];
                j++;
            }
            envp[j] = NULL;
            break; // only remove first match
        }
        i++;
    }
    return envp;
}

// Helps to sort env variables for their names as in the bash
void bubble_sort_envp(char **envp)
{
    int i;
    int j;
    char *temp;

    if (!envp)
        return;
    i = 0;
    while (envp[i])
    {
        j = i + 1;
        while (envp[j])
        {
            if (ft_strcmp(envp[i], envp[j]) > 0)
            {
                temp = envp[i];
                envp[i] = envp[j];
                envp[j] = temp;
            }
            j++;
        }
        i++;
    }
}

//check if name is correct
int is_valid_name(const char *name)
{
    int i;

    if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
        return 0;
    i = 1;
    while (name[i])
    {
        if (!ft_isalnum(name[i]) && name[i] != '_')
            return 0;
        i++;
    }
    return 1;
}
