/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:09:42 by martin            #+#    #+#             */
/*   Updated: 2025/12/14 12:33:09 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_temp_filename(void)
{
	static int	counter = 0;
	char		*counter_str;
	char		*filename;

	counter_str = ft_itoa(counter++);
	if (!counter_str)
		return (NULL);
	filename = ft_strjoin("/tmp/minishell_heredoc_", counter_str);
	free(counter_str);
	return (filename);
}

int	get_input_heredoc_fd(char *delimitter)
{
	char	*line;
	int		fd;
	char	*temp_filename;
	int		read_fd;

	temp_filename = generate_temp_filename();
	if (!temp_filename)
		return (-1);
	fd = open(temp_filename, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("open");
		free(temp_filename);
		return (-1);
	}
	g_signal = 0;
	setup_heredoc_signals();
	while (1)
	{
		line = readline("heredoc>");
		if (!line || g_signal != 0)
		{
			if (!line && g_signal == 0)
				ft_putendl_fd("Warning: here-document delimited by end of file", 2);
			if (line)
			{
				free(line);
			}
			if (g_signal != 0)
			{
				close(fd);
				unlink(temp_filename);
				setup_parent_signals();
				free(temp_filename);
				return (-1);
			}
			break ;
		}
		if (!ft_strcmp(line, delimitter))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	read_fd = open(temp_filename, O_RDONLY, 0600);
	if (read_fd == -1)
	{
		perror("open for reading");
		unlink(temp_filename);
		free(temp_filename);
		return (-1);
	}
	unlink(temp_filename);
	free(temp_filename);
	setup_parent_signals();
	return (read_fd);
}

int	is_redirection_operator(int token_type)
{
	return (token_type == TOKEN_REDIR_IN || token_type == TOKEN_REDIR_APPEND
		|| token_type == TOKEN_REDIR_OUT || token_type == TOKEN_HEREDOC);
}

static t_redir	**cleanup_redir_error(t_redir **redir, t_redir *new_redir)
{
	if (new_redir)
		free(new_redir);
	if (redir)
		ft_free_redirections(redir);
	ft_putendl_fd("malloc error: ast.c redir", 2);
	return (NULL);
}

static t_redir	**append_redir(t_token **current, t_redir **redirection)
{
	t_redir	**temp;
	int		count;

	count = 0;
	while (redirection && redirection[count])
		count++;
	if ((*current)->next->type == TOKEN_WORD)
	{
		temp = ft_realloc(redirection, sizeof(t_redir *) * (count + 1),
				sizeof(t_redir *) * (count + 2));
		if (!temp)
			return (cleanup_redir_error(redirection, NULL));
		redirection = temp;
		redirection[count] = ft_calloc(sizeof(t_redir), 1);
		if (!redirection[count])
			return (cleanup_redir_error(redirection, NULL));
		redirection[count]->type = (*current)->type;
		redirection[count]->target = ft_strdup((*current)->next->value);
		if (!redirection[count]->target)
			return (cleanup_redir_error(redirection, redirection[count]));
		if (redirection[count]->type == TOKEN_HEREDOC)
		{
			redirection[count]->heredoc_fd = get_input_heredoc_fd(redirection[count]->target);
			if (redirection[count]->heredoc_fd == -1)
			{
				cleanup_redir_error(redirection, redirection[count]);
				return NULL;
			}
		}
		count++;
	}
	(*current) = (*current)->next->next;
	redirection[count] = NULL;
	return (redirection);
}

static char	**cleanup_argv_error(char **argv)
{
	ft_putendl_fd("malloc error: ast.c argv", 2);
	if (argv)
		ft_free_split(argv);
	return (NULL);
}

char	**append_argument(t_token **current, t_token *end, char **argv)
{
	int		count;
	char	**temp;

	count = 0;
	while (argv && argv[count])
		count++;
	while (*current && (*current != end)
		&& !is_redirection_operator((*current)->type))
	{
		temp = ft_realloc(argv, sizeof(char *) * (count + 1), sizeof(char *)
				* (count + 2));
		if (!temp)
			return (cleanup_argv_error(argv));
		argv = temp;
		argv[count] = ft_strdup((*current)->value);
		if (!argv[count])
			return (cleanup_argv_error(argv));
		count++;
		*current = (*current)->next;
	}
	argv[count] = NULL;
	return (argv);
}

// token content is already divided, so there wont be any pipe left
int	assign_ast_node(t_token *current, t_token *end, t_ast *ast_node)
{
	while (current && current != end)
	{
		if (current->type == TOKEN_COMMAND || current->type == TOKEN_WORD)
		{
			ast_node->argv = append_argument(&current, end, ast_node->argv);
		}
		else if (is_redirection_operator(current->type))
		{
			ast_node->redir = append_redir(&current, ast_node->redir);
			if (ast_node->redir == NULL)
			{
				return ERROR;
			}
		}
		else
			current = current->next;
	}
	return SUCCESS;
}

t_ast	*create_ast(t_token *start, t_token *end)
{
	t_token	*pipe;
	t_ast	*node;

	if (!start || start == end)
		return (NULL);
	node = ft_calloc(sizeof(t_ast), 1);
	if (!node)
		return (NULL);
	pipe = start;
	while (pipe && pipe != end && pipe->type != TOKEN_PIPE)
		pipe = pipe->next;
	if (pipe && pipe != end && pipe->type == TOKEN_PIPE)
	{
		node->node_type = TOKEN_PIPE;
		node->left = create_ast(start, pipe);
		node->right = create_ast(pipe->next, end);
	}
	else
	{
		node->node_type = TOKEN_COMMAND;
		if(assign_ast_node(start, end, node) == ERROR)
			return NULL;
	}
	return (node);
}

// t_ast	*create_ast(t_token *start, t_token *end)
// {
// 	t_token	*current;
// 	t_token	*least_prio;
// 	t_ast	*new_node;

// 	current = start;
// 	least_prio = current;
// 	if (!start || start == end)
// 		return (NULL);
// 	new_node = ft_calloc(sizeof(t_ast), 1);
// 	if (!new_node)
// 		return (NULL);
// 	while (current && current != end)
// 	{
// 		if (current->type == TOKEN_PIPE)
// 		{
// 			least_prio = current;
// 			break ;
// 		}
// 		current = current->next;
// 	}
// 	if (least_prio->type == TOKEN_PIPE)
// 	{
// 		new_node->node_type = TOKEN_PIPE;
// 		new_node->left = create_ast(start, least_prio);
// 		new_node->right = create_ast(least_prio->next, end);
// 	}
// 	else
// 	{
// 		new_node->node_type = TOKEN_COMMAND;
// 		assign_ast_node(start, end, new_node);
// 	}
// 	return (new_node);
// }
