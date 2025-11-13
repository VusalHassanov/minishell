/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:53:19 by vhasanov          #+#    #+#             */
/*   Updated: 2025/11/13 16:06:41 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// export without arguments
void export_print_all(char **envp)
{
    int i;

    if (!envp)
        return;

    bubble_sort_envp(envp);

    i = 0;
    while (envp[i])
    {
        ft_printf("declare -x %s\n", envp[i]);
        i++;
    }
}

//Splitting to name and path
void split_name_value(const char *str, char **name, char **value)
{
    char *eq_pos;
    
    eq_pos = ft_strchr(str, '=');

    if (eq_pos)
    {
        *name = ft_substr(str, 0, eq_pos - str);
        *value = eq_pos + 1;
    }
    else
    {
        *name = ft_strdup(str);
        *value = NULL;
    }
}


