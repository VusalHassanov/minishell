/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:15:00 by martin            #+#    #+#             */
/*   Updated: 2025/11/30 16:27:41 by martin           ###   ########.fr       */
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

// only if source is quoted, call this function
char	*filter_quotes(const char *source)
{
	char			*dest;
	int				i;
	int				j;
	t_parse_flags	status;

	i = 0;
	j = 0;
	status = (t_parse_flags){0};
	dest = ft_calloc(sizeof(char), ft_strlen(source) + 1);
	if (!dest)
		return (NULL);
	while (source[i])
	{
		if (is_quote_literal(source[i], &status))
			dest[j++] = source[i];
		else if (is_quote(source[i]))
		{
			if (is_open(&status))
				status = (t_parse_flags){0};
			else
				assign_status(source[i], &status);
		}
	}
	return (dest);
}

// int	main(void)
// {
// 	char	string[] = "\"Hello ' World ' \"";

// 	printf("Before: %s\n", string);
// 	printf("After: %s\n", filter_quotes(string));
// 	return (0);
// }

// void	expand_and_filter_tokens(t_token *head)
// {
// 	t_token	*current;

// 	current = head;
// 	while (current)
// 	{
// 		if (current->type == TOKEN_WORD)
// 		{
// 			expand_token_string(current);
// 			filter_quotes(current);
// 		}
// 		current = current->next;
// 	}
// }

// ft_getenv for finding the pointer to the variable name
// char	*expand_string(char *line, char **envp)
// {
// 	// int		i;
// 	// int		variable_len;
// 	// char	*result;
// 	// char	*variable_name;
// 	// i = 0;
// 	// while (line[i])
// 	// {
// 	// 	if (line[i] == '$')
// 	// 	{
// 	// 		while (ft_isprint)
// 	// 		{
// 	// 			variable_len++;
// 	// 			i++;
// 	// 		}
// 	// 	}
// 	// }
// 	return (line);
// }






void expansion(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		//if $ occures in argv[i] (and check syntax)
			// argv[i] = expand_variable(argv[i]);
		//if (quoted(argv[i]))
			// argv[i] = filter_quotes(argv[i]);
		i++;
	}
}

