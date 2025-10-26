/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:50:38 by mgunter           #+#    #+#             */
/*   Updated: 2025/10/26 13:45:31 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_token_type(t_token *token, t_token_type prev_type)
{
	if (prev_type == TOKEN_PIPE || prev_type == TOKEN_NONE)
		token->type = TOKEN_COMMAND;
	else if (token->quote_flag == TOKEN_DOUBLE_QUOTE)
		token->type = TOKEN_DOUBLE_QUOTE;
	else if (token->quote_flag == TOKEN_SINGLE_QUOTE)
		token->type = TOKEN_SINGLE_QUOTE;
	else if (!ft_strcmp(token->value, "|"))
		token->type = TOKEN_PIPE;
	else if (!ft_strcmp(token->value, "<"))
		token->type = TOKEN_REDIR_IN;
	else if (!ft_strcmp(token->value, ">"))
		token->type = TOKEN_REDIR_OUT;
	else if (!ft_strcmp(token->value, "<<"))
		token->type = TOKEN_HEREDOC;
	else if (!ft_strcmp(token->value, ">>"))
		token->type = TOKEN_REDIR_APPEND;
	else
		token->type = TOKEN_WORD;
}

void	assign_all_token_types(t_token *head)
{
	t_token			*current;
	t_token_type	prev_type;

	current = head;
	prev_type = TOKEN_NONE;
	while (current)
	{
		assign_token_type(current, prev_type);
		prev_type = current->type;
		current = current->next;
	}
}

static t_token	*create_token_node(const char *argument)
{
	t_token			*token;
	unsigned int	len;

	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->next = NULL;
	len = ft_strlen(argument);
	if (argument)
	{
		token->value = ft_calloc(sizeof(char), len + 1);
		ft_strlcpy(token->value, argument, len + 1);
	}
	return (token);
}

t_token	*add_token_list(t_token *head, const char *arguments)
{
	t_token	*new_node;
	t_token	*temp;

	new_node = create_token_node(arguments);
	if (!new_node)
		return (NULL);
	if (!head)
		head = new_node;
	else
	{
		temp = head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
	return (head);
}

// // void type_action_handler(t_token *token)

void	type_action_handler(t_token *token)
{
	if (token->type == TOKEN_COMMAND)
		command_handler(token);
	else if (token->value == TOKEN_PIPE)
		ft_pipe(token);
}
