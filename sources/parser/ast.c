/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:09:42 by martin            #+#    #+#             */
/*   Updated: 2025/12/10 16:23:23 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection_operator(int token_type)
{
	return (token_type == TOKEN_REDIR_IN || token_type == TOKEN_REDIR_APPEND
		|| token_type == TOKEN_REDIR_OUT || token_type == TOKEN_HEREDOC);
}

static t_redir	**append_redir(t_token **current, t_redir **redirection)
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
		redirection[count]->type = (*current)->type;
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
			ast_node->argv = append_argument(&current, end, ast_node->argv);
		}
		else if (is_redirection_operator(current->type))
		{
			ast_node->redir = append_redir(&current, ast_node->redir);
		}
		else
			current = current->next;
	}
}

t_ast	*create_ast(t_token *start, t_token *end)
{
    t_token	*pipe;
    t_ast	*node;

    if (!start || start == end)
        return (NULL);
    node = ft_calloc(sizeof(t_ast), 1);
    if (!node)
        return (NULL);
    pipe = start;
    while (pipe && pipe != end && pipe->type != TOKEN_PIPE)
        pipe = pipe->next;
    if (pipe && pipe != end && pipe->type == TOKEN_PIPE)
    {
        node->node_type = TOKEN_PIPE;
        node->left = create_ast(start, pipe);
        node->right = create_ast(pipe->next, end);
    }
    else
    {
        node->node_type = TOKEN_COMMAND;
        assign_ast_node(start, end, node);
    }
    return (node);
}

// t_ast	*create_ast(t_token *start, t_token *end)
// {
// 	t_token	*current;
// 	t_token	*least_prio;
// 	t_ast	*new_node;

// 	current = start;
// 	least_prio = current;
// 	if (!start || start == end)
// 		return (NULL);
// 	new_node = ft_calloc(sizeof(t_ast), 1);
// 	if (!new_node)
// 		return (NULL);
// 	while (current && current != end)
// 	{
// 		if (current->type == TOKEN_PIPE)
// 		{
// 			least_prio = current;
// 			break ;
// 		}
// 		current = current->next;
// 	}
// 	if (least_prio->type == TOKEN_PIPE)
// 	{
// 		new_node->node_type = TOKEN_PIPE;
// 		new_node->left = create_ast(start, least_prio);
// 		new_node->right = create_ast(least_prio->next, end);
// 	}
// 	else
// 	{
// 		new_node->node_type = TOKEN_COMMAND;
// 		assign_ast_node(start, end, new_node);
// 	}
// 	return (new_node);
// }
