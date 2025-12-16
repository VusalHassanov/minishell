/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:50:46 by vhasanov          #+#    #+#             */
/*   Updated: 2025/12/16 20:01:55 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_error(const char *arg)
{
	write(2, "minishell: cd: ", 15);
	if (arg)
		write(2, arg, strlen(arg));
	write(2, ": ", 2);
	write(2, strerror(errno), strlen(strerror(errno)));
	write(2, "\n", 1);
}

// Helper to update environment after successful cd
static void	update_pwd_env(char ***envp, char *oldpwd)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	if (oldpwd && newpwd)
	{
		ft_setenv(envp, "OLDPWD", oldpwd);
		ft_setenv(envp, "PWD", newpwd);
	}
	else if (newpwd)
		ft_setenv(envp, "PWD", newpwd);
	if (newpwd)
		free(newpwd);
}

// Helper for cleanup and return
static int	cd_cleanup(char *oldpwd, char *target, int ret, int free_target)
{
	if (oldpwd)
		free(oldpwd);
	if (free_target && target)
		free(target);
	return (ret);
}

// Main cd function
int	ft_cd(char **args, char ***envp)
{
	char	*oldpwd;
	char	*target;
	int		should_free_target;

	oldpwd = getcwd(NULL, 0);
	target = cd_get_target(args, *envp);
	if (!target)
		return (cd_cleanup(oldpwd, NULL, 1, 0));
	should_free_target = (args[1] && args[1][0] == '~' && args[1][1] == '/');
	if (chdir(target) != 0)
	{
		cd_error(target);
		return (cd_cleanup(oldpwd, target, 1, should_free_target));
	}
	update_pwd_env(envp, oldpwd);
	return (cd_cleanup(oldpwd, target, 0, should_free_target));
}
