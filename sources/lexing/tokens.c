/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 10:16:29 by mgunter           #+#    #+#             */
/*   Updated: 2025/12/15 14:49:58 by mgunter          ###   ########.fr       */
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
		if (token->value == NULL)
		{
			free(token);
			return (NULL);
		}
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
	{
		if (head)
			free_tokens(head);
		return (NULL);
	}
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

static t_token	*create_token_loop(const char *arguments, t_token *head)
{
	char			*token_string;
	unsigned int	original_len;
	t_parse_flags	status;

	status = (t_parse_flags){0};
	while (*arguments)
	{
		skip_whitespace(&arguments);
		if (!*arguments)
			break ;
		token_string = get_token_string(arguments, &status);
		original_len = ft_strlen(token_string);
		token_string = dquote_handler(token_string, &status);
		if (!token_string)
			return (head);
		if (original_len > 0)
			head = add_token_list(head, token_string);
		free(token_string);
		status = (t_parse_flags){0};
		arguments += original_len;
	}
	return (head);
}

t_token	*create_token_list(const char *arguments)
{
	t_token	*head;

	if (!arguments)
		return (NULL);
	head = NULL;
	head = create_token_loop(arguments, head);
	return (head);
}
