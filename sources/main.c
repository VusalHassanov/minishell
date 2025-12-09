/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 22:30:09 by martin            #+#    #+#             */
/*   Updated: 2025/12/09 21:18:55 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_system(t_shell *system)
{
	if (system->token_list)
	{
		free_tokens(system->token_list);
		system->token_list = NULL;
	}
	if (system->ast_root)
	{
		cleanup_ast(system->ast_root);
		system->ast_root = NULL;
	}
	if (system->envp)
	{
		ft_free_split(system->envp);
		system->envp = NULL;
	}
	if (system)
		free(system);
}

// print_nodes(system->token_list);
// print_ast(system->ast_root, 0, 0);
int	input_processing(t_shell *system, char *input)
{
	if (parse_from_string(input, system) == ERROR)
		return (ERROR);
	execute_ast(system->ast_root, system);
	cleanup_ast(system->ast_root);
	system->ast_root = NULL;
	return (SUCCESS);
}
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
int	input_handler(t_shell *system)
{
	char	*input;
	int		signal_status;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		signal_status = check_signal_received();
		if (signal_status != 0)
			system->exit_status = signal_status;
		if (*input)
		{
			add_history(input);
			input_processing(system, input);
		}
		free(input);
	}
	return (system->exit_status);
}

// should minishell quit if environment variable is failed to init?
// setup history pointer (not needed?)
t_shell	*init_system(char **envp)
{
	t_shell	*system;

	system = ft_calloc(sizeof(t_shell), 1);
	if (!system)
		return (NULL);
	system->envp = ft_envdup(envp);
	if (!system->envp)
	{
		free(system);
		ft_putstr_fd("minishell: failed to initialize environment\n", 2);
		return (NULL);
	}
	setup_parent_signals();
	return (system);
}

// free split envp
// cleanup history
// return (system->exit_status);
// exit status as single variable since its not possible to reach after system free
int	main(int argc, char *argv[] __attribute__((unused)), char *envp[])
{
	t_shell	*system;
	int		exit_status;

	if (argc == 1)
	{
		exit_status = 0;
		system = init_system(envp);
		if (system)
		{
			exit_status = input_handler(system);
		}
		rl_clear_history();
		clean_system(system);
		return (exit_status);
	}
	return (ERROR);
}
