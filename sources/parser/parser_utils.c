/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:09:04 by martin            #+#    #+#             */
/*   Updated: 2025/12/16 20:35:17 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator_token(int token_type)
{
	return (token_type == TOKEN_PIPE || token_type == TOKEN_REDIR_IN
		|| token_type == TOKEN_REDIR_OUT || token_type == TOKEN_REDIR_APPEND
		|| token_type == TOKEN_HEREDOC);
}

// int	is_double_operator(int prev_type, int current_type)
// {
// 	if (is_operator_token(prev_type) && is_operator_token(current_type))
// 		return (TRUE);
// 	return (FALSE);
// }

int is_double_operator(int prev_type, int current_type)
{
    if (prev_type == TOKEN_PIPE && (current_type == TOKEN_REDIR_IN
            || current_type == TOKEN_REDIR_OUT
            || current_type == TOKEN_REDIR_APPEND
            || current_type == TOKEN_HEREDOC))
        return (FALSE);
    if (is_operator_token(prev_type) && is_operator_token(current_type))
        return (TRUE);
    return (FALSE);
}

int	check_token_syntax(t_token *head)
{
	int	prev_type;

	prev_type = TOKEN_NONE;
	if (head->type == TOKEN_PIPE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return (ERROR);
	}
	while (head)
	{
		if (is_double_operator(prev_type, head->type)
			|| (is_operator_token(head->type) && !head->next))
		{
			ft_putendl_fd("minishell: syntax error near unexpected token", 2);
			return (ERROR);
		}
		prev_type = head->type;
		head = head->next;
	}
	return (SUCCESS);
}
