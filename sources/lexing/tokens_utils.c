/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:24:52 by mgunter           #+#    #+#             */
/*   Updated: 2025/12/10 16:08:20 by mgunter          ###   ########.fr       */
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

static char	*ft_join_three(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s3);
	free(temp);
	return (result);
}

char	*dquote_handler(char *token_string, t_parse_flags *status)
{
	char	*line;
	char	*new_string;

	while (is_open(status))
	{
		line = readline("dquote> ");
		new_string = ft_join_three(token_string, "\n", line);
		if (!new_string)
			return (NULL);
		free(token_string);
		free(line);
		token_string = new_string;
		if (is_closed(token_string, status))
			return (token_string);
	}
	return (token_string);
}
