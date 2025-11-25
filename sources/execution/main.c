#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

/* forward declaration for resolve_path (defined in execute_helper/search.c) */
char	*resolve_path(char **envp, char *cmd);

int main(int argc, char **argv, char **envp)
{
    char *cmd;
    char *resolved_path;

    if (argc < 2)
    {
        printf("Usage: %s <command>\n", argv[0]);
        return 1;
    }

    cmd = argv[1];

    resolved_path = resolve_path(envp, cmd);
    if (resolved_path)
    {
        printf("Command '%s' resolved to: %s\n", cmd, resolved_path);
        free(resolved_path);
    }
    else
    {
        printf("Command '%s' not found in PATH.\n", cmd);
    }

    return 0;
}
