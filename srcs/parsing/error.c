/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:12:25 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/06 15:11:53 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int check_cmds(t_cmd *cmd)
{
    t_cmd *tmp;

    tmp = cmd;
    while(tmp)
    {
        if(tmp->path == NULL && tmp->type == CMD)
        {
            shell()->error = ft_strjoin(tmp->args[0], " : command not found");
            shell()->status = 127;
            return 0;
        }
        tmp = tmp->next;
    }
    return 1;
}

int error_handler(void)
{
    if(shell()->exit_code != -1)
        return 1;
    shell()->prev_status = shell()->status;
    printf("%s\n", shell()->error);
    free(shell()->error);
    shell()->status = 0;
    return 0;
}