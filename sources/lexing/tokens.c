/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 10:16:29 by mgunter           #+#    #+#             */
/*   Updated: 2025/10/26 21:30:16 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static t_token	*add_token_list(t_token *head, const char *arguments)
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

static char	*get_token_string(const char *arguments, t_parse_flags *status)
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
