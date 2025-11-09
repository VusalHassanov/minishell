/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:15:00 by martin            #+#    #+#             */
/*   Updated: 2025/11/08 19:41:24 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	filter_quotes(char *dest, const char *source, int *quote_flag)
// {
// 	int				i;
// 	int				j;
// 	t_parse_flags	status;

// 	status = (t_parse_flags){0};
// 	i = 0;
// 	j = 0;
// 	while (source[i])
// 	{
// 		if (is_quote_literal(source[i], &status))
// 			dest[j++] = source[i];
// 		else if (is_quote(source[i]))
// 		{
// 			if (is_open(&status))
// 				status = (t_parse_flags){0};
// 			else
// 				assign_status(source[i], &status);
// 			if (source[i] == '\"')
// 				*quote_flag = TOKEN_DOUBLE_QUOTE;
// 			else if (source[i] == '\'')
// 				*quote_flag = TOKEN_SINGLE_QUOTE;
// 		}
// 		else
// 			dest[j++] = source[i];
// 		i++;
// 	}
// 	dest[j] = '\0';
// }

void	filter_quotes(t_token *token)
{
}

void	expand_token_string(t_token *token)
{
}

void	expand_and_filter_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			expand_token_string(current);
			filter_quotes(current);
		}
		current = current->next;
	}
}
