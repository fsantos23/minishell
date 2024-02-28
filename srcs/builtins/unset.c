/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:55:19 by fsantos2          #+#    #+#             */
/*   Updated: 2024/02/27 16:50:44 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void  unset(char **cmd, t_general *shell)
{
  char  *temp;
  int   i;
  int   ar_index;
  char **env;
  
  if (!cmd[1])
  {
    shell->status = 2;
    shell->error = "not enough arguments"; 
  }
  if (cmd[1])
  {
    i = 0;
    while (cmd[++i])
    {
      ar_index = -1;
      while (shell->env[++ar_index])
      {
        temp = get_env_var(shell->env[ar_index]);
				if (!ft_strncmp(cmd[i], temp, ft_strlen(cmd[i])))
				{
					shell->env = rm_str_from_array(shell->env, ar_index);
					free(temp);
					break ;
				}
        free(temp);
      }
    }
  }
}