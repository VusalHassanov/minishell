/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:15:00 by martin            #+#    #+#             */
/*   Updated: 2025/12/15 14:06:41 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	filter_quotes(char *dest, const char *source, int *quote_flag)
// {
// 	int				i;
// 	int				j;
// 	t_parse_flags	status;

// 	status = (t_parse_flags){0};
// 	i = 0;
// 	j = 0;
// 	while (source[i])
// 	{
// 		if (is_quote_literal(source[i], &status))
// 			dest[j++] = source[i];
// 		else if (is_quote(source[i]))
// 		{
// 			if (is_open(&status))
// 				status = (t_parse_flags){0};
// 			else
// 				assign_status(source[i], &status);
// 			if (source[i] == '\"')
// 				*quote_flag = TOKEN_DOUBLE_QUOTE;
// 			else if (source[i] == '\'')
// 				*quote_flag = TOKEN_SINGLE_QUOTE;
// 		}
// 		else
// 			dest[j++] = source[i];
// 		i++;
// 	}
// 	dest[j] = '\0';
// }

// 1) String quoted, not quoted, double quoted handling
// 2) Iterate through string, No dollar sign, return
// 3) If there is a dollar sign,
// but quote follows it return String itself without quotes
// 4) Check after dollar sign:
// 	- If quote, return string without quotes
// 	- If question mark, replace with exit status
// 	- If digit, ignore dollar sign and digit + outside quotes
// 	- If valid variable name,
// replace with env value or empty string if not found
// 5) All functions accepting expansion

void	handle_expansion(char **argv, t_shell *system)
{
	int		i;
	char	*expanded;

	i = 0;
	while (argv[i])
	{
		expanded = expand_string(argv[i], system, 0);
		if (expanded)
		{
			free(argv[i]);
			argv[i] = expanded;
		}
		i++;
	}
}

char	*expand_string(char *str, t_shell *system, int expand_flag)
{
	char	*result;
	char	*final;
	int		i;

	i = 0;
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	while (result[i])
	{
		if (result[i] == '$')
		{
			if (expand_flag || !is_in_single_quotes(result, i))
				result = expand_variable(result, &i, system, expand_flag);
			else
				i++;
		}
		else
			i++;
	}
	if(expand_flag)
		return (result);
	final = remove_quotes(result);
	free(result);
	return (final);
}

char	*expand_variable(char *str, int *i, t_shell *system, int in_heredoc)
{
	char	*result;

	if (str[*i + 1] == '?')
		result = expand_exit_status(str, *i, system->exit_status);
	else if (str[*i + 1] == '\0' || str[*i + 1] == ' ')
	{
		(*i)++;
		return (str);
	}
	// In heredoc, quotes are NOT special - don't skip them
	else if (!in_heredoc && (str[*i + 1] == '\'' || str[*i + 1] == '\"'))
	{
		(*i)++;
		return (str);
	}
	else
		result = expand_env_var(str, *i, system->envp);
	if (result != str)
		free(str);
	*i = 0;
	return (result);
}
