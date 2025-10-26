/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:50:38 by mgunter           #+#    #+#             */
/*   Updated: 2025/10/26 16:47:21 by martin           ###   ########.fr       */
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

t_token	*add_token_list(t_token *head, const char *arguments)
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
