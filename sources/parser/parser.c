/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:50:00 by martin            #+#    #+#             */
/*   Updated: 2025/12/16 19:20:17 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void assign_token_type(t_token *token, t_token_type prev_type)
{
    if (!ft_strcmp(token->value, "|"))
        token->type = TOKEN_PIPE;
    else if (!ft_strcmp(token->value, "<"))
        token->type = TOKEN_REDIR_IN;
    else if (!ft_strcmp(token->value, ">"))
        token->type = TOKEN_REDIR_OUT;
    else if (!ft_strcmp(token->value, "<<"))
        token->type = TOKEN_HEREDOC;
    else if (!ft_strcmp(token->value, ">>"))
        token->type = TOKEN_REDIR_APPEND;
    else if (prev_type == TOKEN_REDIR_IN || prev_type == TOKEN_REDIR_OUT
        || prev_type == TOKEN_HEREDOC || prev_type == TOKEN_REDIR_APPEND)
        token->type = TOKEN_WORD;
    else if (prev_type == TOKEN_PIPE || prev_type == TOKEN_NONE)
        token->type = TOKEN_COMMAND;
    else
        token->type = TOKEN_WORD;
}

// static void	assign_token_type(t_token *token, t_token_type prev_type)
// {
// 	if (!ft_strcmp(token->value, "|"))
// 		token->type = TOKEN_PIPE;
// 	else if (!ft_strcmp(token->value, "<"))
// 		token->type = TOKEN_REDIR_IN;
// 	else if (!ft_strcmp(token->value, ">"))
// 		token->type = TOKEN_REDIR_OUT;
// 	else if (!ft_strcmp(token->value, "<<"))
// 		token->type = TOKEN_HEREDOC;
// 	else if (!ft_strcmp(token->value, ">>"))
// 		token->type = TOKEN_REDIR_APPEND;
// 	else if (prev_type == TOKEN_PIPE || prev_type == TOKEN_NONE)
// 		token->type = TOKEN_COMMAND;
// 	else
// 		token->type = TOKEN_WORD;
// }

static void	assign_all_token_types(t_token *head)
{
	t_token			*current;
	t_token_type	prev_type;

	current = head;
	prev_type = TOKEN_NONE;
	while (current)
	{
		assign_token_type(current, prev_type);
		prev_type = current->type;
		current = current->next;
	}
}

int	parse_from_string(const char *arguments, t_shell *system)
{
	system->token_list = create_token_list(arguments);
	if (!system->token_list)
		return (ERROR);
	assign_all_token_types(system->token_list);
	if (check_token_syntax(system->token_list) == ERROR)
	{
		free_tokens(system->token_list);
		system->token_list = NULL;
		return (ERROR);
	}
	system->ast_root = create_ast(system->token_list, NULL, system);
	free_tokens(system->token_list);
	system->token_list = NULL;
	if (!system->ast_root)
		return (ERROR);
	return (SUCCESS);
}
