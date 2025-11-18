/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:58:36 by martin            #+#    #+#             */
/*   Updated: 2025/11/18 16:07:38 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	int		i;
	char	*builtin[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit",
			NULL};

	i = 0;
	while (builtin[i])
	{
		if (!ft_strcmp(builtin[i], command))
			return (1);
		i++;
	}
	return (0);
}

int	set_up_redirections(t_ast *node)
{
	int		i;
	t_redir	**current;

	// setup every type of redirections with FDs.
	current = node->redir;
	i = 0;
	while (current[i])
	{
		if (!current[i]->target)
		{
			return (0);
		}
		if (current[i]->type == TOKEN_REDIR_IN)
		{
			// call function with target as argument
		}
		else if (current[i]->type == TOKEN_REDIR_APPEND)
		{
			// call function with target as argument
		}
		else if (current[i]->type == TOKEN_REDIR_OUT)
		{
			// call function with target as argument
		}
		else if (current[i]->type == TOKEN_HEREDOC)
		{
			// call function with target as argument
		}
		i++;
	}
}

int	execution_handler(t_ast *node)
{
	// build logic for processing command leafs
	// after setup all FDs are in proper position,
	// so argv just has to be executed
	if (!set_up_redirections(node))
	{
		return (0);
	}
	if (is_builtin(node->argv[0]))
	{
		// call builtin handler
		// execute_buildin(node->argv,)
	}
	else
	{
		// find the path function to the commands
		// create child process, call new pgm with execve (needs path!)
		// execve("PATH/FOLDER/ls", "node->argv[0]", NULL);
	}
	return (1);
}

void	execute_ast(t_ast *node, int depth)
{
	printf(RED "LEVEL:[%d]\n" RESET, depth);
	if (!node)
	{
		return ;
	}
	if (node->node_type == TOKEN_PIPE)
	{
		create_pipe(node, depth);
	}
	else
	{
		printf(RED "COMMAND CALL ON LEVEL [%d]\n" RESET, depth);
		if (!execution_handler(node))
		{
			printf("oh no! execution handling error!\n");
		}
	}
}
