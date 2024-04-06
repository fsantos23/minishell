/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:50:17 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/06 15:24:48 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_exit(char **cmd)
{
    int i;
    int a;

    i = 1;
    a = 0;
    while(cmd[i])
    {
        a = 0;
        if(i == 2 && !shell()->error)
        {
            shell()->error = ft_strdup("too many arguments");
            shell()->status = 1;
            return ;
        }
        while(cmd[i][a] && i < 2)
        {
            if((cmd[i][0] == '-' || cmd[i][0] == '+') && a == 0)
                a++;
            if(!ft_isdigit(cmd[i][a]))
            {
                shell()->error = ft_strdup("not a valid argument");
                break ;
            }
            a++;
        }
        i++;
    }
    if(cmd[1])
        shell()->exit_code = ft_atoi(cmd[1]);
    else
        shell()->exit_code = 0;
    shell()->prompt = false;
    printf("exit\n");
}
