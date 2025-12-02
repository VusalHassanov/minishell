/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:50:46 by vhasanov          #+#    #+#             */
/*   Updated: 2025/12/02 18:50:49 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void cd_error(const char *arg)
{
    write(2, "minishell: cd: ", 15);
    if (arg)
        write(2, arg, strlen(arg));
    write(2, ": ", 2);
    write(2, strerror(errno), strlen(strerror(errno)));
    write(2, "\n", 1);
}

int ft_cd(char **args, char ***envp)
{
    char *oldpwd;
    char *target;

    oldpwd = getcwd(NULL, 0);
    if (!oldpwd)
    {
        cd_error(NULL);   // unlikely, but safe
        return 1;
    }

    target = cd_get_target(args, *envp);
    if (!target)
    {
        free(oldpwd);
        return 1;
    }

    if (chdir(target) != 0)
    {
        cd_error(target);
        free(oldpwd);
        return 1;
    }

    update_env(envp, oldpwd);
    free(oldpwd);
    return 0;
}
