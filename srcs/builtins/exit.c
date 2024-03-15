/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:50:17 by fsantos2          #+#    #+#             */
/*   Updated: 2024/03/05 14:40:32 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_exit(char **cmd)
{
    int	i;

    printf("exit\n");
    i = -1;
    while (cmd && cmd[1] && cmd[1][++i])
    {
        if (i == 0 && (cmd[1][0] == '+' || cmd[1][0] == '-'))
            continue ;
        else if (!ft_isdigit(cmd[1][i]))
        {
            write(STDERR_FILENO, " numeric argument required\n", 27);
            break ;
        }
        else if (cmd[1][i + 1] == '\0' && cmd[2])
        {
            write(STDERR_FILENO, " too many arguments\n", 20);
        }
    }
    shell()->prompt = false;
}