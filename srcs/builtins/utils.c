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

void rm_str_from_array(char ***array, int index)
{
    if (!(*array))
        return;

    int len = 0;
    while ((*array)[len])
        len++;

    // allocating memory for the new array
    char **new_array = malloc(sizeof(char *) * (len + 1));
    if (!new_array)
        return;

    int i = 0;
    int j = 0;
    while ((*array)[i])
    {
        // if current index is not the one to be removed, copy the string to the new array
        if (i != index)
        {
            new_array[j] = strdup((*array)[i]);
            // if strdup failed (returned NULL), free the already allocated memory and return
            if (!new_array[j])
            {
                new_array[j+1] = NULL;        // mark the end of the successfully created string array
                free_array(new_array);        // free the new_array
                return;
            }
            j++;
        }
        i++;
    }
    new_array[j] = NULL; // marking the end of the new array

    // free the old array after making sure new_array is properly allocated
    free_array2(array);
    *array = new_array;
}

void add_str_to_array(char ***array, char *str)
{
    if (!(*array) || !str)
        return;
    int len = 0;
    while ((*array)[len])
        len++;
    char **new_array = malloc(sizeof(char *) * (len + 2));
    if (!new_array)
        return;
    int i = 0;
    while(i < len)
    {
        new_array[i] = strdup((*array)[i]);
        if (!new_array[i])                // if strdup failed (returned NULL)
        {
            new_array[i+1] = NULL;        // mark the end of the successfully created string array
            free_array(new_array);        // free the new_array
            return;
        }
        i++;
    }

    new_array[len] = strdup(str);
    if (!new_array[len])
    {
        new_array[len + 1] = NULL;
        free_array(new_array);           // free the new_array if strdup failed here
        return;
    }
    new_array[len + 1] = NULL;
    free_array2(array);
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
