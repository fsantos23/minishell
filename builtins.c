/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaopereira <joaopereira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:22:09 by joaopereira       #+#    #+#             */
/*   Updated: 2024/02/21 14:49:44 by joaopereira      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_builtins(char *cmd)
{
  if (ft_strcmp(cmd, "cd") == 0)
    cd();
  else if (!ft_strcmp(cmd(0), "export"))
    export();
  else if (!ft_strcmp(cmd(0), "unset"))
    unset();
  else if (!ft_strcmp(cmd(0), "env"))
    env();
  else if (!ft_strcmp(cmd(0), "exit"))
    exit();
  else if (!ft_strcmp(cmd(0), "echo"))
    echo();
  else if (!ft_strcmp(cmd(0), "pwd"))
    pwd ();
  else
    return;
}