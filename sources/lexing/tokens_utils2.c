/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:39:03 by mgunter           #+#    #+#             */
/*   Updated: 2025/12/15 12:40:40 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quote(const char *arguments, unsigned int len,
		t_parse_flags *status)
{
	if (is_no_quote(status))
		assign_status(arguments[len], status);
	else if (is_quote_matching(arguments[len], status))
		*status = (t_parse_flags){0};
}

int	should_break(const char *arguments, unsigned int len, t_parse_flags *status)
{
	if (!arguments[len])
		return (TRUE);
	if (is_no_quote(status) && is_whitespace(arguments[len]))
		return (TRUE);
	if (is_no_quote(status) && is_shell_operator(arguments[len]))
	{
		if (len > 0)
			return (TRUE);
		return (TRUE);
	}
	return (FALSE);
}

char	*get_token_string(const char *arguments, t_parse_flags *status)
{
	unsigned int	len;
	char			*result;

	len = 0;
	while (arguments[len])
	{
		if (is_quote(arguments[len]))
			handle_quote(arguments, len, status);
		else if (should_break(arguments, len, status))
			break ;
		len++;
	}
	if (len == 0 && is_shell_operator(arguments[0]))
	{
		if (arguments[0] == arguments[1])
			len = 2;
		else
			len = 1;
	}
	result = ft_calloc(sizeof(char), len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, arguments, len + 1);
	return (result);
}
