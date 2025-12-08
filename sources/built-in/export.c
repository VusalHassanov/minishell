/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:20:50 by vhasanov          #+#    #+#             */
/*   Updated: 2025/11/25 18:29:43 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("`: not a valid identifier\n", 2);
		}
		else if (value != NULL)
			ft_setenv(envp, name, value);
		else
			ft_setenv(envp, name, NULL);
		free(name);
		i++;
	}
	return (0);
}
