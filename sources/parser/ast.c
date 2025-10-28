/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:09:42 by martin            #+#    #+#             */
/*   Updated: 2025/10/28 13:59:18 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection_operator(int token_type)
{
	return (token_type == TOKEN_REDIR_IN || token_type == TOKEN_REDIR_APPEND
		|| token_type == TOKEN_REDIR_OUT || token_type == TOKEN_HEREDOC);
}

t_redir *append_redir(void)
{
	
}

void	*append_argument(void *list, char *argument)
{
}

void	assign_ast_node(t_token *current, t_token *end, t_ast *ast_node)
{
	int		argument_count;
	int		redirection_count;
	char	**temp;

	argument_count = 0;
	redirection_count = 0;
	while (current && current != end)
	{
		if (is_redirection_operator(current->type))
		{
			
		}
		if (current->type == TOKEN_COMMAND)
		{
			// takes arguments
		}
		current = current->next;
	}
}

t_ast	*create_ast(t_token *start, t_token *end)
{
	t_token	*current;
	t_token	*least_prio;
	t_ast	*new_node;

	current = start;
	least_prio = current;
	if (!start || start == end)
		return (NULL);
	new_node = ft_calloc(sizeof(t_ast), 1);
	if (!new_node)
		return (NULL);
	while (current && current != end)
	{
		if (current->type == TOKEN_PIPE)
		{
			least_prio = current;
			break ;
		}
		current = current->next;
	}
	if (least_prio->type == TOKEN_PIPE)
	{
		new_node->node_type = TOKEN_PIPE;
		new_node->left = create_ast(start, least_prio);
		new_node->right = create_ast(least_prio->next, end);
	}
	else
	{
		new_node->node_type = TOKEN_COMMAND;
		assign_ast_node(start, end, new_node);
	}
	return (new_node);
}
