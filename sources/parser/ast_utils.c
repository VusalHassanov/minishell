/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:26:29 by martin            #+#    #+#             */
/*   Updated: 2025/11/10 12:41:16 by martin           ###   ########.fr       */
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
		free(root->redir[i]);
		i++;
	}
	if (root->redir)
		free(root->redir);
	free(root);
}
