/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:48:39 by martin            #+#    #+#             */
/*   Updated: 2025/11/18 18:49:42 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ROOT 0
#define LEFT 1
#define RIGHT 2

char	*strings[] = {"TOKEN_NONE", "TOKEN_WORD", "TOKEN_COMMAND", "TOKEN_PIPE",
		"TOKEN_REDIR_IN", "TOKEN_REDIR_OUT", "TOKEN_REDIR_APPEND",
		"TOKEN_HEREDOC", "TOKEN_AND", "TOKEN_OR", NULL};

void	print_argv(char **string, int depth)
{
	int	i;
	int	j;

	i = 0;
	while (string[i])
	{
		j = 0;
		while (j <= depth)
		{
			printf("   ");
			j++;
		}
		printf("Argument [%d]: [%s]\n", i, string[i]);
		i++;
	}
}

void	print_redir(t_redir **node, int depth)
{
	int	i;
	int	j;

	i = 0;
	while (node[i])
	{
		j = 0;
		while (j <= depth)
		{
			printf("   ");
			j++;
		}
		printf(CYAN "Redirection [%d]: [%s]\t" RESET, i,
			strings[node[i]->type]);
		printf(CYAN "Target [%d]: [%s]\n" RESET, i, node[i]->target);
		i++;
	}
}

void	print_ast(t_ast *head, int depth, int node_position)
{
	int	i;
	int	j;

	if (!head)
		return ;
	i = 0;
	while (i++ < depth)
		printf("   ");
	if (node_position == LEFT)
		printf(BLUE "LEFT:" RESET);
	else if (node_position == RIGHT)
		printf(BLUE "RIGHT:" RESET);
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
			print_argv(head->argv, depth);
		if (head->redir)
			print_redir(head->redir, depth);
	}
}

void	print_nodes(t_token *head)
{
	t_token	*temp;

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
