/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:01:41 by vhasanov          #+#    #+#             */
/*   Updated: 2025/11/13 17:07:18 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *cd_get_target(t_token *args, char **envp)
{
    t_token *target_token = args->next;
    if (!target_token)
    {
        char *home = ft_getenv(envp, "HOME");
        if (!home)
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            return NULL;
        }
        return home;
    }
    return target_token->value;
}



