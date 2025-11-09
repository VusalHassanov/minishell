/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:09:42 by martin            #+#    #+#             */
/*   Updated: 2025/11/09 17:09:10 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection_operator(int token_type)
{
	return (token_type == TOKEN_REDIR_IN || token_type == TOKEN_REDIR_APPEND
		|| token_type == TOKEN_REDIR_OUT || token_type == TOKEN_HEREDOC);
}

// append redirections on multiple function calls since 2nd word after red ist again argv
t_redir	**append_redir(t_token **current, t_token *end, t_redir **redirection)
{
	t_redir	**temp;
	int		count;

	count = 0;
	while (redirection && redirection[count])
		count++;
	if ((*current)->next->type == TOKEN_WORD)
	{
		temp = ft_realloc(redirection, sizeof(t_redir *) * (count + 1),
				sizeof(t_redir *) * (count + 2));
		if (!temp)
		{
			// implement error handling
			return (NULL);
		}
		redirection = temp;
		redirection[count] = ft_calloc(sizeof(t_redir), 1);
		(*redirection)->type = (*current)->type;
		redirection[count]->target = ft_strdup((*current)->next->value);
		count++;
	}
	(*current) = (*current)->next->next;
	redirection[count] = NULL;
	return (redirection);
}

char	**append_argument(t_token **current, t_token *end, char **argv)
{
	int		count;
	char	**temp;

	count = 0;
	while (argv && argv[count])
		count++;
	while (*current && (*current != end)
		&& !is_redirection_operator((*current)->type))
	{
		temp = ft_realloc(argv, sizeof(char *) * (count + 1), sizeof(char *)
				* (count + 2));
		if (!temp)
		{
			// add free function if realloc causes an error
			return (NULL);
		}
		argv = temp;
		argv[count] = ft_strdup((*current)->value);
		count++;
		*current = (*current)->next;
	}
	argv[count] = NULL;
	return (argv);
}

// token list is already divided, so there wont be any pipe left
void	assign_ast_node(t_token *current, t_token *end, t_ast *ast_node)
{
	while (current && current != end)
	{
		if (current->type == TOKEN_COMMAND || current->type == TOKEN_WORD)
		{
			// takes arguments and append to list
			ast_node->argv = append_argument(&current, end, ast_node->argv);
		}
		else if (is_redirection_operator(current->type))
		{
			ast_node->redir = append_redir(&current, end, ast_node->redir);
		}
		else
			current = current->next;
	}
}
// after first occurance of pipe the list will get divided by recursive functioncall
// otherwise all commands will just appear in the same command node
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
