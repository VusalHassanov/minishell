/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:18:21 by vhasanov          #+#    #+#             */
/*   Updated: 2025/11/19 19:24:30 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_echo(char **argv)
{
    int i;
    int newline;
    
    i = 1;
    newline = 1;
    while (argv[i] && is_n_flag(argv[i]))
    {
        newline = 0;
        i++;
    }
    while (argv[i])
    {
        printf("%s", argv[i]);
        if (argv[i + 1])
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
    return 0;
}


