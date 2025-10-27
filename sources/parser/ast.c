/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:09:42 by martin            #+#    #+#             */
/*   Updated: 2025/10/27 22:07:23 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection_operator(int token_type)
{
	return (token_type == TOKEN_REDIR_IN || token_type == TOKEN_REDIR_APPEND
		|| token_type == TOKEN_REDIR_OUT || token_type == TOKEN_HEREDOC);
}

t_ast	*create_ast(t_token *start, t_token *end)
{
	t_token *current;
	t_token *least_prio;
	t_ast *new_node;

	current = start;
	if (!current)
		return (NULL);
	new_node = ft_calloc(sizeof(t_ast), 1);
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			least_prio = current;

			break ;
		}
		current++;
	}
	new_node->left = create_ast(start, current - 1);
	new_node->right = create_ast(current + 1, end);
	return (new_node);
}