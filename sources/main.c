/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 22:30:09 by martin            #+#    #+#             */
/*   Updated: 2025/11/18 15:36:15 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int input_handler(t_shell *system)
{
	// readline stdin
	// check signals received (signal status)
	// if readline = true  add history
	// system->token_list = create_token_list(input)
	// syntax checker
	// system->ast = create_ast(system->token_list, NULL)
	// free token_list if ast is properly done
	// execute_ast (system->ast, 0);
	// free (AST)
	// free input
	// return (system->exit_status);
}


t_shell	*init_system(void)
{
	t_shell	*system;

	system = ft_calloc(sizeof(t_shell), 1);
	if (!system)
		return (NULL);
	// setup environment variables
	// setup parent signals
	// setup history pointer
	return (system);
}

int	main(void)
{
	t_shell	*system;

	system = init_system();
	if (!system)
		return (system->exit_status);
	// system->exit_status = input handler(system);
	// free split envp
	// cleanup memory (system)
	// cleanup history
	// return system->exit_status;
}
