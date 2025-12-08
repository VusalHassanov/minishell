/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:08:30 by mgunter           #+#    #+#             */
/*   Updated: 2025/11/25 19:04:18 by martin           ###   ########.fr       */
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
		return (TRUE);
	return (FALSE);
}

// Checks if the on character pointing quote is opened
int	is_open(t_parse_flags *status)
{
	if (status->double_quote == QUOTE_OPEN
		|| status->single_quote == QUOTE_OPEN)
		return (TRUE);
	return (FALSE);
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
		return (TRUE);
	return (FALSE);
}
