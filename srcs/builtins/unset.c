/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:55:19 by fsantos2          #+#    #+#             */
/*   Updated: 2024/03/05 14:40:15 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
int check_unset_conditions(char *str)
{
    int i;

    // Variable name must start with a letter or underscore
    if (!(ft_isalpha(str[0]) || str[0] == '_'))
        return (0);

    i = 0;
    while (str[++i])
    {
        if (str[i] == '=')
            return (0);
        if (!(ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_'))
            return (0);
    }
    return (1);
}

void  unset(char **cmd)
{
  char  *temp;
  int   i;
  int   ar_index;

  if (!cmd[1])
  {
    shell()->status = 2;
    shell()->error = "not enough arguments";
    return ;
  }
  if (cmd[1])
  {
    i = 0;
    while (cmd[++i])
    {
      ar_index = -1;
      while (shell()->env[++ar_index])
      {
          if (!check_unset_conditions(cmd[i]))
          {
              shell()->error = "invalid parameter name";
              shell()->status = 2;
              return ;
          }
          temp = get_env_var(shell()->env[ar_index]);
          if (ft_strcmp(cmd[i], temp) == 0)
          {
              rm_str_from_array(&shell()->env, ar_index);
              free(temp);
              break ;
          }
          free(temp);
      }
    }
  }
}