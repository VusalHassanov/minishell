#include "minishell.h"

int ft_exit_tokens(t_token *args)
{
    t_token *arg;
    int status;
	
	arg = args->next;
    ft_putstr_fd("exit\n", 1);
    if (!arg)
        exit(0);
    if (!is_numeric(arg->value))
    {
        ft_putstr_fd("minishell: exit: ", 2);
        ft_putstr_fd(arg->value, 2);
        ft_putstr_fd(": numeric argument required\n", 2);
        exit(255);
    }
    status = ft_atoi(arg->value) % 256;
    if (arg->next)
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        return 1;
    }
    exit(status);
}
