/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:24:52 by mgunter           #+#    #+#             */
/*   Updated: 2025/12/15 12:24:03 by mgunter          ###   ########.fr       */
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

int	dquote_end_of_file(char *line, char **token_string)
{
	if (!line || g_signal == SIGINT)
	{
		if (*token_string)
		{
			free(*token_string);
			*token_string = NULL;
		}
		if (line)
			free(line);
		return (TRUE);
	}
	else
		return (FALSE);
}

char	*dquote_handler(char *token_string, t_parse_flags *status)
{
	char	*line;
	char	*new_string;

	new_string = NULL;
	setup_dquote_signals();
	while (is_open(status))
	{
		line = readline("dquote> ");
		if (dquote_end_of_file(line, &token_string) == TRUE)
			break ;
		new_string = ft_strjoin_three(token_string, "\n", line);
		free(token_string);
		free(line);
		if (!new_string)
			return (NULL);
		token_string = new_string;
		if (is_closed(token_string, status))
			return (token_string);
	}
	setup_parent_signals();
	return (token_string);
}
