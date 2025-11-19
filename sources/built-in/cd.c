/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:18:12 by vhasanov          #+#    #+#             */
/*   Updated: 2025/11/18 19:32:38 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cd(char **args, char ***envp)
{
    char *oldpwd;
    char *target;

    oldpwd = getcwd(NULL, 0);
    if (!oldpwd)
    {
        perror("cd");
        return (1);
    }
    target = cd_get_target(args, *envp);
    if (!target)
    {
        free(oldpwd);
        return (1);
    }
    if (chdir(target) != 0)
    {
        perror("cd");
        free(oldpwd);
        return (1);
    }
    update_env(envp, oldpwd);
    free(oldpwd);
    return (0);
}