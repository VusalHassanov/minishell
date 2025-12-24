/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:53:33 by vhasanov          #+#    #+#             */
/*   Updated: 2025/12/22 12:03:12 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **argv, char ***envp)
{
	int	i;

	i = 1;
	if (!argv || !argv[1])
		return (0);
	while (argv[i])
	{
		if (is_valid_name(argv[i]))
			*envp = envp_remove(*envp, argv[i]);
		i++;
	}
	return (0);
}

// int	ft_unset(char **argv, char ***envp)
// {
// 	int	i;

// 	i = 1;
// 	if (!argv)
// 		return (0);
// 	while (argv[i])
// 	{
// 		if (!is_valid_name(argv[i]))
// 			printf("unset: '%s': not a valid identifier\n", argv[i]);
// 		else
// 			envp_remove(*envp, argv[i]);
// 		i++;
// 	}
// 	return (0);
// }
