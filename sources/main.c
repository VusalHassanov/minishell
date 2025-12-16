/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 22:30:09 by martin            #+#    #+#             */
/*   Updated: 2025/12/16 19:37:33 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_system(t_shell *system)
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

static int	input_processing(t_shell *system, char *input)
{
	if (parse_from_string(input, system) == ERROR)
		return (ERROR);
	execute_ast(system->ast_root, system);
	cleanup_ast(system->ast_root);
	system->ast_root = NULL;
	return (SUCCESS);
}

static int	input_handler(t_shell *system)
{
	char	*input;
	char	*line;
	int		signal_status;

	while (1)
	{
		signal_status = check_signal_received();
		if (signal_status != 0)
			system->exit_status = signal_status;
		if (isatty(fileno(stdin)))
			input = readline("minishell$ ");
		else
		{
			line = get_next_line(fileno(stdin));
			if (!line)
				break ;
			input = ft_strtrim(line, "\n");
			free(line);
		}
		if (!input)
		{
			if (isatty(fileno(stdin)))
				printf("exit\n");
			break ;
		}
		if (*input)
		{
			if (isatty(fileno(stdin)))
				add_history(input);
			input_processing(system, input);
		}
		free(input);
	}
	return (system->exit_status);
}

static t_shell	*init_system(char **envp)
{
	t_shell	*system;

	system = ft_calloc(sizeof(t_shell), 1);
	if (!system)
		return (NULL);
	system->envp = ft_envdup(envp);
	if (!system->envp)
	{
		free(system);
		// ft_putstr_fd("minishell: failed to initialize environment\n", 2);
		return (NULL);
	}
	setup_parent_signals();
	return (system);
}

int	main(int argc, char *argv[], char *envp[])
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
	return (FAILURE);
}
