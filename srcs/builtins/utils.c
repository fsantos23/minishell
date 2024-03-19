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

void	rm_str_from_array(char ***array, int index)
{
    char	**new_array;
    int		len;
    int		i;

    if (!(*array))
        return ;
    else
    {
        len = 0;
        while ((*array)[len])
            len++;
        new_array = malloc(sizeof(char *) * len);
        if (!new_array)
            return ;
        i = -1;
        len = 0;
        while ((*array)[++i])
        {
            if (i != index)
                new_array[len++] = ft_strdup((*array)[i]);
        }
        new_array[len] = NULL;
        *array = new_array;
    }
}
void add_str_to_array(char ***array, char *str)
{
    int len;
    len = 0;

    while ((*array)[len])
        len++;

    char **new_array = malloc(sizeof(char *) * (len + 2));
    if (!new_array)
        return;

    int i = 0;
    while(i < len) {
        new_array[i] = strdup((*array)[i]);
        i++;
    }

    new_array[len] = strdup(str);
    new_array[len + 1] = NULL;

    *array = new_array;
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

int	ft_strcmp(char *s1, char *s2)
{
    int	i;

    i = 0;
    if (!s1 || !s2)
        return (-1);
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            break ;
        i++;
    }
    return (s1[i] - s2[i]);
}
