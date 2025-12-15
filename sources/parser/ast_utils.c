/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:26:29 by martin            #+#    #+#             */
/*   Updated: 2025/12/15 13:22:15 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection_operator(int token_type)
{
	return (token_type == TOKEN_REDIR_IN || token_type == TOKEN_REDIR_APPEND
		|| token_type == TOKEN_REDIR_OUT || token_type == TOKEN_HEREDOC);
}

t_redir	**cleanup_redir_error(t_redir **redir, t_redir *new_redir)
{
	if (new_redir)
		free(new_redir);
	if (redir)
		ft_free_redirections(redir);
	ft_putendl_fd("malloc error: ast.c redir", 2);
	return (NULL);
}

void	cleanup_ast(t_ast *root)
{
	int	i;

	if (!root)
		return ;
	cleanup_ast(root->left);
	cleanup_ast(root->right);
	i = 0;
	while (root->argv && root->argv[i])
		free(root->argv[i++]);
	if (root->argv)
		free(root->argv);
	i = 0;
	while (root->redir && root->redir[i])
	{
		if (root->redir[i]->target)
			free(root->redir[i]->target);
		if (root->redir[i]->heredoc_fd > 0)
			close(root->redir[i]->heredoc_fd);
		free(root->redir[i]);
		i++;
	}
	if (root->redir)
		free(root->redir);
	free(root);
}

void	ft_free_redirections(t_redir **redir)
{
	int	i;

	i = 0;
	while (redir[i])
	{
		free(redir[i]->target);
		free(redir[i]);
		i++;
	}
	free(redir);
}

char	**cleanup_argv_error(char **argv)
{
	ft_putendl_fd("malloc error: ast.c argv", 2);
	if (argv)
		ft_free_split(argv);
	return (NULL);
}
