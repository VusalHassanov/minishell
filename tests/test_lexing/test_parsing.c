/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:43:34 by mgunter           #+#    #+#             */
/*   Updated: 2025/11/09 17:08:19 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <signal.h>

#define ROOT 0
#define LEFT 1
#define RIGHT 2

void	print_ast(t_ast *head, int depth, int node_position)
{
	int	i;
	int	j;

	if (!head)
		return ;
	i = 0;
	while (i < depth)
	{
		printf("   ");
		i++;
	}
	if (node_position == LEFT)
	{
		printf(BLUE "LEFT:" RESET);
	}
	else if (node_position == RIGHT)
	{
		printf(BLUE "RIGHT:" RESET);
	}
	if (head->node_type == TOKEN_PIPE)
	{
		if (depth == 0)
			printf(YELLOW "ROOT PIPE\n" RESET);
		else
			printf("PIPE Node\n");
		print_ast(head->left, depth + 1, LEFT);
		print_ast(head->right, depth + 1, RIGHT);
	}
	else
	{
		printf("COMMAND Node:\n");
		if (head->argv)
		{
			i = 0;
			while (head->argv[i])
			{
				j = 0;
				while (j <= depth)
				{
					printf("   ");
					j++;
				}
				printf("Argument [%d]: [%s]\n", i, head->argv[i]);
				i++;
			}
		}
		if (head->redir)
		{
			i = 0;
			while (head->redir[i])
			{
				j = 0;
				while (j <= depth)
				{
					printf("   ");
					j++;
				}
				printf("Redirection [%d]: [%d]\t", i, head->redir[i]->type);
				printf("Target [%d]: [%s]\n", i, head->redir[i]->target);
				i++;
			}
		}
	}
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
		printf(GREEN "Token Type: [%s]\t\tToken String: [%s]\n" WHITE,
			strings[temp->type], temp->value);
		temp = temp->next;
	}
}

void	cleanup_ast(t_ast *node)
{
	int	i;

	if (!node)
		return ;
	cleanup_ast(node->left);
	cleanup_ast(node->right);
	if (node->argv)
	{
		i = 0;
		while (node->argv[i])
		{
			free(node->argv[i]);
			i++;
		}
		free(node->argv);
	}
	if (node->redir)
	{
		i = 0;
		while (node->redir[i])
		{
			free(node->redir[i]->target);
			free(node->redir[i]);
			i++;
		}
		free(node->redir);
	}
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
			print_ast(system->ast_root, 0, ROOT);
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
