/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:50:00 by martin            #+#    #+#             */
/*   Updated: 2025/10/27 19:09:55 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_token_type(t_token *token, t_token_type prev_type)
{
	if (prev_type == TOKEN_PIPE || prev_type == TOKEN_NONE)
		token->type = TOKEN_COMMAND;
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

t_token	*parse_tokens_from_string(const char *arguments)
{
	t_token *head;

	head = create_token_list(arguments);
	assign_all_token_types(head);
	// expand_and_filter_tokens(head);
	return (head);
}
