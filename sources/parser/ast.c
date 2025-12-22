/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:09:42 by martin            #+#    #+#             */
/*   Updated: 2025/12/22 11:43:54 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir	*fill_redirection_node(t_shell *system, t_redir **head,
		t_token_type type, char *value)
{
	t_redir	*redirection;

	redirection = ft_calloc(sizeof(t_redir), 1);
	if (!redirection)
		return (NULL);
	redirection->type = type;
	redirection->target = ft_strdup(value);
	if (!redirection->target)
	{
		free(redirection);
		return (NULL);
	}
	if (redirection->type == TOKEN_HEREDOC)
	{
		redirection->heredoc_fd = get_input_heredoc_fd(redirection->target,
				system);
		if (redirection->heredoc_fd == -1)
		{
			free(redirection->target);
			free(redirection);
			return (NULL);
		}
	}
	return (redirection);
}

static t_redir	**append_redir(t_token **current, t_redir **redirection,
		t_shell *system)
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
			return (cleanup_redir_error(redirection, NULL));
		redirection = temp;
		redirection[count] = fill_redirection_node(system, redirection,
				(*current)->type, (*current)->next->value);
		if (!redirection[count])
			return (cleanup_redir_error(redirection, NULL));
		count++;
	}
	(*current) = (*current)->next->next;
	redirection[count] = NULL;
	return (redirection);
}

static char	**append_argument(t_token **current, t_token *end, char **argv)
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
			return (cleanup_argv_error(argv));
		argv = temp;
		argv[count] = ft_strdup((*current)->value);
		if (!argv[count])
			return (cleanup_argv_error(argv));
		count++;
		*current = (*current)->next;
	}
	argv[count] = NULL;
	return (argv);
}

// token content is already divided, so there wont be any pipe left
static int	assign_ast_node(t_token *current, t_token *end, t_ast *ast_node,
		t_shell *system)
{
	while (current && current != end)
	{
		if (current->type == TOKEN_COMMAND || current->type == TOKEN_WORD)
		{
			ast_node->argv = append_argument(&current, end, ast_node->argv);
		}
		else if (is_redirection_operator(current->type))
		{
			ast_node->redir = append_redir(&current, ast_node->redir, system);
			if (ast_node->redir == NULL)
			{
				return (ERROR);
			}
		}
		else
			current = current->next;
	}
	return (SUCCESS);
}

t_ast	*create_ast(t_token *start, t_token *end, t_shell *system)
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
		node->left = create_ast(start, pipe, system);
		node->right = create_ast(pipe->next, end, system);
	}
	else
	{
		node->node_type = TOKEN_COMMAND;
		if (assign_ast_node(start, end, node, system) == ERROR)
			return (NULL);
	}
	return (node);
}
