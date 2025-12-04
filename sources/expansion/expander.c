/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:15:00 by martin            #+#    #+#             */
/*   Updated: 2025/12/04 18:56:12 by vhasanov         ###   ########.fr       */
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
// 3) If there is a dollar sign, but quote follows it return String itself without quotes
// 4) Check after dollar sign:
// 	- If quote, return string without quotes
// 	- If question mark, replace with exit status
// 	- If digit, ignore dollar sign and digit + outside quotes
// 	- If valid variable name, replace with env value or empty string if not found
// 5) All functions accepting expansion

char *handle_expansion(char *str, t_shell *system)
{
    char *result;
    int i;
    
    i = 0;
    result = ft_strdup(str);
    if (!result)
        return (NULL);
    while (result[i])
    {
        if (result[i] == '$')
            result = expand_variable(result, &i, system);
        else
            i++;
    }
    return (result);
}

char *expand_variable(char *str, int *i, t_shell *system)
{
    char *result;
    
    if (str[*i + 1] == '?')
        result = expand_exit_status(str, *i, system->exit_status);
    else if (str[*i + 1] == '\0' || str[*i + 1] == ' ')
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

void	filter_quotes(t_token *token)
{
}

void	expand_token_string(t_token *token)
{
}

void	expand_and_filter_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			expand_token_string(current);
			filter_quotes(current);
		}
		current = current->next;
	}
}
