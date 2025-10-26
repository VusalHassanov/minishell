/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 10:16:29 by mgunter           #+#    #+#             */
/*   Updated: 2025/10/21 21:29:19 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token_string(const char *arguments, t_parse_flags *status)
{
	unsigned int	len;
	char			*result;

	len = 0;
	while (arguments[len])
	{
		if (is_quote(arguments[len]))
		{
			if (is_no_quote(status))
				assign_status(arguments[len], status);
			else if (is_quote_matching(arguments[len], status))
				*status = (t_parse_flags){0};
		}
		else if (is_no_quote(status) && is_whitespace(arguments[len]))
			break ;
		else if (is_no_quote(status) && is_shell_operator(arguments[len]))
		{
			if (arguments[len] == arguments[len + 1])
				len = 2;
			else
				len = 1;
			break ;
		}
		else if (!arguments[len])
			break ;
		len++;
	}
	result = ft_calloc(sizeof(char), len + 1);
	ft_strlcpy(result, arguments, len + 1);
	return (result);
}

char	*dquote_handler(char *token_string, t_parse_flags *status)
{
	char	*temp;
	char	*temp2;
	char	*line;

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

t_token	*create_token_list(const char *arguments)
{
	t_token			*head;
	char			*token_string;
	unsigned int	original_len;
	t_parse_flags	status;

	status = (t_parse_flags){0};
	if (!arguments)
		return (NULL);
	head = NULL;
	while (*arguments)
	{
		skip_whitespace(&arguments);
		if (!*arguments)
			break ;
		token_string = get_token_string(arguments, &status);
		original_len = ft_strlen(token_string);
		if (is_open(&status))
			token_string = dquote_handler(token_string, &status);
		if (original_len > 0)
			head = add_token_list(head, token_string);
		free(token_string);
		status = (t_parse_flags){0};
		arguments += original_len;
	}
	return (head);
}

// void	expand_and_filter_tokens(t_token *head)
// {
// 	t_token	*current;
// 	char	*temp;

// 	current = head;
// 	while (current)
// 	{
// 		if (current->type == TOKEN_DOUBLE_QUOTE)
// 		{
// 			//expand value
// 		}
// 		else if (current->type == TOKEN_SINGLE_QUOTE)
// 		{
// 			//expand value
// 		}
// 		else if (current->type == TOKEN_MIXED_QUOTE)
// 		{
// 			//expand value
// 		}
// 		current = current->next;
// 	}
// }

t_token	*parse_tokens_from_string(const char *arguments)
{
	t_token	*head;

	head = create_token_list(arguments);
	assign_all_token_types(head);
	// expand_and_filter_tokens(head);
	return (head);
}
