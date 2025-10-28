/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:43:34 by mgunter           #+#    #+#             */
/*   Updated: 2025/10/28 13:39:12 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <signal.h>

void	print_ast(t_ast *head)
{
	if (!head)
		return ;
	print_ast(head->left);
	print_ast(head->right);
	printf("%d\n", head->node_type);
}

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

void	cleanup_ast(t_ast *node)
{
	if (!node)
		return ;
	cleanup_ast(node->left);
	cleanup_ast(node->right);
	free(node);
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
		parse_from_string(line, system);
		if (system->token_list)
		{
			print_nodes(system->token_list);
			free_tokens(system->token_list);
			print_ast(system->ast_root);
			cleanup_ast(system->ast_root);
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
	line = readline("minishell$ ");
	while (line != NULL)
	{
		stdout_handler(line);
		free(line);
		line = readline("minishell$ ");
	}
	return (0);
}
