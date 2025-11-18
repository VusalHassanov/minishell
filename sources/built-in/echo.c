/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:18:21 by vhasanov          #+#    #+#             */
/*   Updated: 2025/11/18 12:04:56 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_echo(t_token *args)
{
    t_token *current = args->next; // skip "echo"
    int newline = 1;

    if (current && is_n_flag(current->value))
    {
        newline = 0;
        while (current && is_n_flag(current->value))
            current = current->next;
    }
    while (current)
    {
        printf("%s", current->value);
        if (current->next)
            printf(" ");
        current = current->next;
    }
    if (newline)
        printf("\n");
    return 0;
}
