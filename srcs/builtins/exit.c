/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:50:17 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/06 15:04:46 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>




void	ft_exit(char **cmd)
{
    int i;
    int a;

    printf("exit\n");
    i = 1;
    a = 0;
    while(cmd[i])
    {
        a++;
        if(i == 2 && !shell()->error)
        {
            shell()->error = ft_strdup("too many arguments");
            shell()->status = "";
            return ;
        }
        while(cmd[i][a])
        {
            if(!ft_isdigit(cmd[i][a]))
                shell()->error = ft_strdup("not a valid argument");
        }
        i++;
    }
    shell()->prompt = false;
}
