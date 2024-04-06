/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:46:42 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/06 15:10:18 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int builtins(char **arg)
{
  if(!ft_strncmp(arg[0], "env", 4) && arg[1] == NULL)
    return 1;
  else if(!ft_strncmp(arg[0], "pwd", 4) && arg[1] == NULL)
    return 1;
  else if(!ft_strncmp(arg[0], "cd", 3))
    return 1;
  else if(!ft_strncmp(arg[0], "exit", 5))
    return 1;
  else if(!ft_strncmp(arg[0], "export", 7))
    return 1;
  else if(!ft_strncmp(arg[0], "echo", 5))
    return 1;
  else if(!ft_strncmp(arg[0], "unset", 5))
    return 1;
  return 0;
}

void execute_builtins(int in, int out, t_cmd *cmd)
{
  int origin_in;
  int origin_out;
  
  origin_in = dup(STDIN_FILENO);
  origin_out = dup(STDOUT_FILENO);
  dup2(in, STDIN_FILENO);
  dup2(out, STDOUT_FILENO);
  close_fd(in, out);
  if (!ft_strcmp(cmd->args[0], "cd"))
    cd(cmd->args);
  else if (!ft_strcmp(cmd->args[0], "export"))
    export(cmd->args);
  else if (!ft_strcmp(cmd->args[0], "unset"))
    unset(cmd->args);
  else if (!ft_strcmp(cmd->args[0], "env"))
    env(cmd->args);
  else if (!ft_strcmp(cmd->args[0], "exit"))
    ft_exit(cmd->args);
  else if (!ft_strcmp(cmd->args[0], "echo"))
    echo(cmd->args);
  else if (!ft_strcmp(cmd->args[0], "pwd"))
    pwd();
  dup2(origin_in, STDIN_FILENO);
  dup2(origin_out, STDOUT_FILENO);
}
