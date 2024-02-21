#include <minishell.h>

void ft_exit(char **cmd)
{
    if (!cmd || ft_strcmp(cmd[0], "exit"))
        return;

    printf("exit\n");

    int i = -1;

    while (cmd && cmd[1] && cmd[1][++i])
    {
        if (i == 0 && (cmd[1][0] == '+' || cmd[1][0] == '-'))
            continue;
        else if (!ft_isdigit(cmd[1][i]))
        {
            write(STDERR_FILENO, " numeric argument required\n", 27);
            exit(2);
        }
        else if (cmd[1][i + 1] == '\0' && cmd[2])
        {
            write(STDERR_FILENO, " too many arguments\n", 20);
            exit(1);
        }
        else if (cmd[1][i + 1] == '\0')
        {
            exit(ft_atoi(cmd[1]));
        }
    }

    exit(0);
}


