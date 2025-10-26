#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**cmd_args;
	int		exit_status;
	int		signal_status;

	(void)argc;
	(void)argv;
	exit_status = 0;
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
			cmd_args = ft_split(input, ' ');
			if (ft_strcmp(cmd_args[0], "pwd") == 0)
				ft_pwd();
			else if (ft_strcmp(cmd_args[0], "echo") == 0)
				ft_echo(cmd_args);
			else if (ft_strcmp(cmd_args[0], "env") == 0)
				ft_env(envp);
			else if (ft_strcmp(cmd_args[0], "exit") == 0)
				ft_exit(cmd_args);
			ft_free_split(cmd_args);
		}
		free(input);
	}
	rl_clear_history();
	return (exit_status);
}
