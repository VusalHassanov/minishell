/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:26:29 by martin            #+#    #+#             */
/*   Updated: 2025/12/14 11:53:18 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
