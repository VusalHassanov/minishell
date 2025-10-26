/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_checker2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:16:55 by mgunter           #+#    #+#             */
/*   Updated: 2025/10/21 10:57:57 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char character)
{
	return (character == '"' || character == '\'');
}

int	is_quote_literal(char character, t_parse_flags *status)
{
	if (status->double_quote == QUOTE_OPEN && character == '\'')
		return (1);
	if (status->single_quote == QUOTE_OPEN && character == '"')
		return (1);
	return (0);
}

int	is_quote_matching(char character, t_parse_flags *status)
{
	if (status->double_quote == QUOTE_OPEN && character == '"')
		return (1);
	if (status->single_quote == QUOTE_OPEN && character == '\'')
		return (1);
	return (0);
}

int	is_shell_operator(char character)
{
	int	i;
	char	operator[] = {
		'>', '<', '|', '&', '(', ')', 0};

	i = 0;
	while (operator[i])
	{
		if (operator[i] == character)
		{
			return (1);
		}
		i++;
	}
	return (0);
}
