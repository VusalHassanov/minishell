/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:20:50 by vhasanov          #+#    #+#             */
/*   Updated: 2025/11/14 22:38:12 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_export(t_token *args, char ***envp)
{
    t_token *current;
    char *name;
    char *value;

    if (!args || !args->next)
    {
        export_print_all(*envp);
        return 0;
    }
    current = args->next;
    while (current)
    {
        split_name_value(current->value, &name, &value);
        if (!is_valid_name(name))
            printf("export: '%s': not a valid identifier\n", current->value);
        else if (value)
            ft_setenv(envp, name, value);
        free(name);
        current = current->next;
    }
    return 0;
}