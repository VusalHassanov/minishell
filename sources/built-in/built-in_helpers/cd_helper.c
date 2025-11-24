/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:01:41 by vhasanov          #+#    #+#             */
/*   Updated: 2025/11/19 19:19:25 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *cd_get_target(char **argv, char **envp)
{
    if (argv[1] == NULL)
    {
        char *home = ft_getenv(envp, "HOME");
        if (!home)
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            return NULL;
        }
        return home;
    }
    return argv[1];
}




