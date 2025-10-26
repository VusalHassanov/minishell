/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:24:52 by mgunter           #+#    #+#             */
/*   Updated: 2025/10/21 19:53:10 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	filter_quotes(char *dest, const char *source, int *quote_flag)
{
	int				i;
	int				j;
	t_parse_flags	status;

	status = (t_parse_flags){0};
	i = 0;
	j = 0;
	while (source[i])
	{
		if (is_quote_literal(source[i], &status))
			dest[j++] = source[i];
		else if (is_quote(source[i]))
		{
			if (is_open(&status))
				status = (t_parse_flags){0};
			else
				assign_status(source[i], &status);
			if (source[i] == '\"')
				*quote_flag = TOKEN_DOUBLE_QUOTE;
			else if (source[i] == '\'')
				*quote_flag = TOKEN_SINGLE_QUOTE;
		}
		else
			dest[j++] = source[i];
		i++;
	}
	dest[j] = '\0';
}
void	skip_whitespace(const char **string)
{
	while (**string && (is_whitespace(**string)))
	{
		(*string)++;
	}
}

// a quote can only be opened if both types have QUOTE_NONE status
void	assign_status(char character, t_parse_flags *status)
{
	if (character == '\"')
	{
		if (is_no_quote(status))
			status->double_quote = QUOTE_OPEN;
	}
	else if (character == '\'')
		if (is_no_quote(status))
			status->single_quote = QUOTE_OPEN;
}

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	if (!tokens)
		return ;
	while (tokens != NULL)
	{
		temp = tokens->next;
		if (tokens->value)
			free(tokens->value);
		free(tokens);
		tokens = temp;
	}
}
