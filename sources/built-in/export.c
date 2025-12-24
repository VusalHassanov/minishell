/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:20:50 by vhasanov          #+#    #+#             */
/*   Updated: 2025/12/22 11:22:21 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *argument, char *name)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(argument, 2);
	ft_putstr_fd("`: not a valid identifier\n", 2);
	free(name);
}

int	ft_export(char **argv, char ***envp)
{
	char	*name;
	char	*value;
	int		i;

	i = 1;
	if (!argv[i])
	{
		export_print_all(*envp);
		return (0);
	}
	while (argv[i])
	{
		split_name_value(argv[i], &name, &value);
		if (!is_valid_name(name))
		{
			print_error(argv[i], name);
			return (1);
		}
		ft_setenv(envp, name, value);
		free(name);
		i++;
	}
	return (0);
}

// int	ft_export(char **argv, char ***envp)
// {
// 	char	*name;
// 	char	*value;
// 	int		i;

// 	i = 1;
// 	if (!argv[i])
// 	{
// 		export_print_all(*envp);
// 		return (0);
// 	}
// 	while (argv[i])
// 	{
// 		split_name_value(argv[i], &name, &value);
// 		if (!is_valid_name(name))
// 		{
// 			ft_putstr_fd("export: `", 2);
// 			ft_putstr_fd(argv[i], 2);
// 			ft_putstr_fd("`: not a valid identifier\n", 2);
// 			free(name);
// 			return (1);
// 		}
// 		else if (value != NULL)
// 			ft_setenv(envp, name, value);
// 		else
// 			ft_setenv(envp, name, NULL);
// 		free(name);
// 		i++;
// 	}
// 	return (0);
// }