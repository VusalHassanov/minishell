/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 00:00:00 by vhasanov          #+#    #+#             */
/*   Updated: 2025/11/14 22:49:25 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int execute_builtin(t_token *tokens, char ***envp)
{
    if (!tokens || !tokens->value)
        return (0);

    if (ft_strcmp(tokens->value, "pwd") == 0)
        return (ft_pwd());
    else if (ft_strcmp(tokens->value, "echo") == 0)
        return (ft_echo(tokens));
    else if (ft_strcmp(tokens->value, "env") == 0)
        return (ft_env(*envp));
    else if (ft_strcmp(tokens->value, "exit") == 0)
        return (ft_exit_tokens(tokens));
    else if (ft_strcmp(tokens->value, "cd") == 0)
        return (ft_cd(tokens, envp));
    else if (ft_strcmp(tokens->value, "export") == 0)
        return (ft_export(tokens, envp));
    else if (ft_strcmp(tokens->value, "unset") == 0)
        return (ft_unset(tokens, envp));
    else
    {
        printf("minishell: %s: command not found\n", tokens->value);
        return (127);
    }
}

int main(int argc, char **argv, char **envp)
{
    char    *input;
    t_token *tokens;
    char    **my_envp;
    int     exit_status;
    int     signal_status;

    (void)argc;
    (void)argv;
    exit_status = 0;
    my_envp = ft_envdup(envp);
    if (!my_envp)
    {
        ft_putstr_fd("minishell: failed to initialize environment\n", 2);
        return (1);
    }
    setup_parent_signals();
    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
        {
            printf("exit\n");
            break ;
        }
        signal_status = check_signal_received();
        if (signal_status != 0)
            exit_status = signal_status;
        if (*input)
        {
            add_history(input);
            tokens = create_token_list(input);
            if (tokens)
            {
                exit_status = execute_builtin(tokens, &my_envp);
                free_tokens(tokens);
            }
        }
        free(input);
    }
    ft_free_split(my_envp);
    rl_clear_history();
    return (exit_status);
}