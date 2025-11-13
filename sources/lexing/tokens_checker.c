/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:08:30 by mgunter           #+#    #+#             */
/*   Updated: 2025/10/20 17:36:12 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char character)
{
	return (character == ' ' || character == '\t');
}

//  checks if any quote is open
int	is_no_quote(t_parse_flags *status)
{
	if (status->double_quote == QUOTE_NONE
		&& status->single_quote == QUOTE_NONE)
		return (1);
	return (0);
}

// Checks if the on character pointing quote is opened
int	is_open(t_parse_flags *status)
{
	if (status->double_quote == QUOTE_OPEN
		|| status->single_quote == QUOTE_OPEN)
		return (1);
	return (0);
}

int	is_closed(char *string, t_parse_flags *status)
{
	*status = (t_parse_flags){0};
	while (*string)
	{
		if (is_quote(*string) && is_open(status))
		{
			if (is_quote_matching(*string, status))
				*status = (t_parse_flags){0};
		}
		else if (is_quote(*string))
			assign_status(*string, status);
		string++;
	}
	if (!is_open(status))
		return (1);
	return (0);
}
