/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaopereira <joaopereira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:29:23 by joaopereira       #+#    #+#             */
/*   Updated: 2024/02/21 14:49:36 by joaopereira      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_variable_size(char *str)
{
  int i;

  i = 0;
  if (!str)
    return (0);
  while (str[i] && str[i] != '=')
    i++;
  return (i);
}

void expander(char **cmd, char **env)
{
  int i = -1;
  while (cmd && cmd[++i])
  {
    int j = -1;
    while (cmd[i][++j])
    {
      if (cmd[i][j] == '$')
      {
        int size = get_variable_size(&cmd[i][j + 1]);
        char *variable = ft_substr(&cmd[i][j + 1], 0, size);
        char *value = get_env_value(variable, env);
        char *new = ft_strjoin(ft_substr(cmd[i], 0, j), value);
        char *temp = ft_strjoin(new, &cmd[i][j + size + 1]);

        free(new);
        free(cmd[i]);
        cmd[i] = temp;
        free(variable);
        free(value);
      }
    }
  }
}

void get_env_value(char *variable, char **env)
{
  int i = -1;
  while (env && env[++i])
  {
    if (ft_strncmp(env[i], variable, ft_strlen(variable)) == 0)
      return (ft_strchr(env[i], '=') + 1);
  }
  return (NULL);
}