/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 22:30:09 by martin            #+#    #+#             */
/*   Updated: 2025/11/10 22:34:27 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_system(void)
{
	t_shell	*system;

	system = ft_calloc(sizeof(t_shell), 1);
	if (!system)
		return (NULL);
    
	return (system);
}

int	main(void)
{
	t_shell *system;

	system = init_system();
	if (!system)
		return (EXIT_FAILURE);

	// empty
}