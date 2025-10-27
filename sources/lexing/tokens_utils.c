/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:24:52 by mgunter           #+#    #+#             */
/*   Updated: 2025/10/26 21:26:40 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*dquote_handler(char *token_string, t_parse_flags *status)
{
	char *temp;
	char *temp2;
	char *line;

	while (is_open(status))
	{
		line = readline("dquote> ");
		temp = ft_strjoin(token_string, "\n");
		if (!temp)
			return (NULL);
		temp2 = ft_strjoin(temp, line);
		if (!temp2)
		{
			free(temp);
			return (NULL);
		}
		free(token_string);
		free(line);
		free(temp);
		token_string = temp2;
		if (is_closed(token_string, status))
			return (token_string);
	}
	return (token_string);
}