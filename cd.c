/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaopereira <joaopereira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:30:59 by joaopereira       #+#    #+#             */
/*   Updated: 2024/02/21 14:42:07 by joaopereira      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cd(char **cmd) {
  char *temp;
  int i;
  int ar_index;

  if (!cmd || ft_strcmp(cmd[0], "cd") != 0)
    return;

  if (cmd[1]) 
  {
    i = 0;
    while (cmd[++i]) 
    {
      ar_index = -1;
      while (shell()->env[++ar_index]) 
      {
          temp = get_env_var(shell()->env[ar_index]);
          if (ft_strcmp(cmd[i], temp) == 0) 
          {
            rm_str_from_array(&shell()->env, ar_index);
            free(temp);
            break;
          }
        free(temp);
      }
    }
  }
}