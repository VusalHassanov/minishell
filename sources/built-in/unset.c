/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:53:33 by vhasanov          #+#    #+#             */
/*   Updated: 2025/11/22 19:29:03 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_unset(char **argv, char ***envp)
{
    int i;
    
    i = 1;
    if (!argv)
        return 0;
    while (argv[i])
    {
        if (!is_valid_name(argv[i]))
            printf("unset: '%s': not a valid identifier\n", argv[i]);
        else
            envp_remove(envp, argv[i]);
        i++;
    }
    return 0;
}


