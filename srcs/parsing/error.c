/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:12:25 by fsantos2          #+#    #+#             */
/*   Updated: 2024/02/28 14:54:55 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void check_cmds(t_cmd *cmd, t_general *shell)
{
    t_cmd *tmp;

    tmp = cmd;
    while(tmp)
    {
        if(tmp->path == NULL && tmp->type == CMD)
        {
            shell->error = ft_strjoin("command not found: ", tmp->args[0]);
            shell->status = 127;
        }
        tmp = tmp->next;
    }
}

int error_handler(t_general *shell)
{
    if(shell->exit_code == 1)
        return 1;
    shell->prev_status = shell->status;
    printf("pre_status: %d\n", shell->prev_status);
    printf("%s\n", shell->error);
    shell->status = 0;
    return 0;
}