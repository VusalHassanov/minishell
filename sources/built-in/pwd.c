/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:18:47 by vhasanov          #+#    #+#             */
/*   Updated: 2025/11/13 12:18:48 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd()
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if(!cwd)
        return 1;
    printf("%s\n", cwd);
    free(cwd);
    return 0;
}