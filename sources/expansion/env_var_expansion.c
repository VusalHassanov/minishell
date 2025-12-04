/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 18:54:45 by vhasanov          #+#    #+#             */
/*   Updated: 2025/12/04 18:57:58 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_env_var(char *str, int pos, char **env)
{
    char *var_name;
    char *var_value;
    char *result;
    
    var_name = extract_var_name(str, pos + 1);
    if (!var_name)
        return (str);
    var_value = get_env_value(var_name, env);
    free(var_name);
    if (!var_value)
        return (remove_var(str, pos));
    result = replace_var(str, pos, var_value);
    return (result);
}

char *extract_var_name(char *str, int start)
{
    char *name;
    int i;
    int len;
    
    i = start;
    len = 0;
    while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
    {
        len++;
        i++;
    }
    name = malloc(len + 1);
    if (!name)
        return (NULL);
    i = 0;
    while (i < len)
    {
        name[i] = str[start + i];
        i++;
    }
    name[i] = '\0';
    return (name);
}

char *get_env_value(char *var_name, char **env)
{
    int i;
    int j;
    int len;
    
    i = 0;
    len = ft_strlen(var_name);
    while (env[i])
    {
        j = 0;
        while (env[i][j] && env[i][j] != '=')
            j++;
        if (j == len && ft_strncmp(env[i], var_name, len) == 0)
            return (env[i] + j + 1);
        i++;
    }
    return (NULL);
}