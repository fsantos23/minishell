/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:46:42 by fsantos2          #+#    #+#             */
/*   Updated: 2024/03/05 14:41:23 by fsantos2         ###   ########.fr       */
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
  else if(!ft_strncmp(arg[0], "exit", 5) && arg[1] == NULL)
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
  if (!ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])))
    cd(cmd->args);
  else if (!ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0])))
    export(cmd->args);
  else if (!ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0])))
    unset(cmd->args);
  else if (!ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0])))
    env();
  else if (!ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0])))
    ft_exit();
  else if (!ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0])))
    echo(cmd->args);
  else if (!ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])))
    pwd();
  dup2(origin_in, STDIN_FILENO);
  dup2(origin_out, STDOUT_FILENO);
}