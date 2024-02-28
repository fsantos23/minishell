/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 17:21:21 by fsantos2           #+#    #+#             */
/*   Updated: 2023/12/23 17:21:21 by fsantos2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* void check_quotes(char **args, t_cmd *cmd)
{
    int i;
    int a;
    char *expand;
    char *flag;

    i = 0;
    flag = NULL;
    expand = NULL;
    while(args[i])
    {
        a = 0;
        if(args[i][0] == '\"')
        {
            while(args[i][a])
            {
                if(args[i][a] == "$")
                    flag = args[i][a];
                if(flag == "$" && args[i][a] != ' ')
                    expand = args[i][a];
                a++;
            }
            if(args[i][a] == '\"')
                args = ft_strtrim(args, '\"');
            else
            {
                printf("close the quotes\n");
                exit(1);
            }
        }
        else if(args[0] == '\'')
        {
            while(args[i][a])
                a++;
            if(args[i][a] == '\'')
                args = ft_strtrim(args, '\'');
            else
            {
                printf("close the quotes\n");
                exit(1);
            }
        }
        if(expand)
            cmd->expand = ft_strdup(expand);
        cmd->args[i] = args[i];
        i++;
    }
} */

/* void check_quotes(t_cmd *cmd)
{
    t_cmd *tmp;

    tmp = cmd;
    while(tmp)
    {
        while(tmp->ins)
        {
            check_redir(tmp->ins);
            tmp->ins = tmp->ins->next;
        }
        while(tmp->outs)
        {
            check_redir(tmp->outs);
            tmp->outs = tmp->outs->next;
        }
        tmp = tmp->next;
    }
} */