/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:43:34 by mgunter           #+#    #+#             */
/*   Updated: 2025/10/27 22:01:18 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <signal.h>

void	print_nodes(t_token *head)
{
	t_token	*temp;
	char	*strings[] = {"TOKEN_NONE", "TOKEN_WORD", "TOKEN_COMMAND",
			"TOKEN_PIPE", "TOKEN_REDIR_IN", "TOKEN_REDIR_OUT",
			"TOKEN_REDIR_APPEND", "TOKEN_HEREDOC", "TOKEN_AND", "TOKEN_OR",
			NULL};

	if (!head)
		return ;
	temp = head;
	while (temp)
	{
		printf(GREEN "Token Type: [%s]\tToken String: [%s]\n" WHITE,
			strings[temp->type], temp->value);
		temp = temp->next;
	}
}

void	cleanup_tokens(t_token **tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free_tokens(tokens[i]);
		i++;
	}
	free(tokens);
}

void	argv_handler(int argc, char *argv[])
{
	t_token	**tokens;
	int		i;

	tokens = ft_calloc(argc, sizeof(t_token *));
	if (!tokens)
		return ;
	i = 1;
	while (i < argc)
	{
		printf(YELLOW "[%d] Commandstring:\n%s\n" WHITE, i, argv[i]);
		tokens[i - 1] = parse_tokens_from_string(argv[i]);
		if (!tokens[i - 1])
			return (cleanup_tokens(tokens, i - 1));
		print_nodes(tokens[i - 1]);
		i++;
	}
	cleanup_tokens(tokens, argc - 1);
}

void	stdout_handler(char *line)
{
	t_shell	*system;
	int		len;

	system = ft_calloc(sizeof(t_shell), 1);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (ft_strlen(line) > 0)
	{
		system->token_list = parse_tokens_from_string(line);
		if (system->token_list)
		{
			print_nodes(system->token_list);
			free_tokens(system->token_list);
			free(system);
		}
	}
}

void	sigint_handler(int signum)
{
	(void)signum;
	exit(0);
}

int	main(int argc, char *argv[])
{
	char	*line;

	signal(SIGINT, sigint_handler);
	if (argc > 1)
	{
		argv_handler(argc, argv);
	}
	else
	{
		line = readline("minishell$ ");
		while (line != NULL)
		{
			stdout_handler(line);
			free(line);
			line = readline("minishell$ ");
		}
	}
	return (0);
}
