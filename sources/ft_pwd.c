#include "minishell.h"

int ft_pwd()
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if(!cwd)
        return 1;
    printf("%s\n", cwd);
    free(cwd);
    return 0;
}