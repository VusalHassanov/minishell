#include "minishell.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args)
{
	int	status;

	printf("exit\n");
	if (!args[1])
		exit(0);
	if (!is_numeric(args[1]))
	{
		fprintf(stderr, "minishell: exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}
	status = ft_atoi(args[1]) % 256;
	exit(status);
}
