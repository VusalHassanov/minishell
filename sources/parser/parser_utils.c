/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:09:04 by martin            #+#    #+#             */
/*   Updated: 2025/11/09 12:08:40 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_operator_token(int token_type)
{
	return (token_type == TOKEN_PIPE || token_type == TOKEN_REDIR_IN
		|| token_type == TOKEN_REDIR_OUT || token_type == TOKEN_REDIR_APPEND
		|| token_type == TOKEN_HEREDOC);
}

int	is_double_operator(int prev_type, int current_type)
{
	if (is_operator_token(prev_type) && is_operator_token(current_type))
		return (0);
	return (1);
}

int	check_token_syntax(t_token *head)
{
	int prev_type;
	prev_type = TOKEN_NONE;
	if (head->type == TOKEN_PIPE)
	{
        printf(RED"First token is a pipe!\n"WHITE);
		return (0);
	}
	while (head)
	{
		if (!is_double_operator(prev_type, head->type))
		{
			printf(RED"Invalid Syntax!\n"WHITE);
			return (0);
		}
		prev_type = head->type;
		head = head->next;
	}
	return (1);
}