/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:53:23 by fsantos2          #+#    #+#             */
/*   Updated: 2024/02/21 19:07:12 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char  **rm_str_from_array(char **array, int index)
{
  char	**new;
  int	i;
  int	j;

  i = 0;
  j = -1;
  if (!array || !(array)[index])
    return NULL;
  while (array[i])
    i++;
  new = malloc(sizeof(char *) * i);
  if (!new)
    return NULL;
  i = -1;
  while (array[++i])
  {
    if (i != index)
      new[++j] = ft_strdup(array[i]);
  }
  free_array(array);
  return new;
}

char **add_str_to_array(char **array, char *str)
{
  char	**new;
  int	i;

  i = 0;
  if (!array || !str)
    return NULL;
  while (array[i])
    i++;
  new = malloc(sizeof(char *) * (i+ 2));
  if (!new)
    return NULL;
  i = -1;
  while ((array)[++i])
    new[i] = ft_strdup((array)[i]);
  new[i++] = ft_strdup(str);
  new[i] = NULL;
  free_array(array);
  return (new);
}


char	*get_env_var(char *str)
{
	int		i;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

char	**copy_array(char **array)
{
	char	**new;
	int		i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (array[++i])
		new[i] = ft_strdup(array[i]);
	new[i] = NULL;
	return (new);
}