/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:53:33 by vhasanov          #+#    #+#             */
/*   Updated: 2025/11/18 12:09:53 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_unset(t_token *args, char ***envp)
{
    t_token *current;

    if (!args || !args->next)
        return 0;

    current = args->next;
    while (current)
    {
        if (!is_valid_name(current->value))
            printf("unset: '%s': not a valid identifier\n", current->value);
        else
            envp_remove(*envp, current->value);
        current = current->next;
    }
    return 0;
}
