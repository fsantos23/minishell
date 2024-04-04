/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:30:30 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/03 17:00:42 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void update_env(char ***env, char *new) {
    char **existing_var_split;
    char **new_var_split;
    int i;

    if (!env || !new)
        return;
    new_var_split = ft_split(new, '=');
    i = -1;
    while ((*env)[++i]) {
        existing_var_split = ft_split((*env)[i], '=');

        if (ft_strcmp(existing_var_split[0], new_var_split[0]) == 0)
        {
            char* duplicated_new = NULL;
            if (ft_strchr(new, '=') != NULL)
            {
                duplicated_new = ft_strdup(new);
                free((*env)[i]);
                (*env)[i] = duplicated_new;
            }
            free_array(existing_var_split);
            free_array(new_var_split);
            return;
        }
        free_array(existing_var_split);
    }

    add_str_to_array(env, new);
    free_array(new_var_split);
}

void	print_env(char	**env)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	while (env && env[++i])
	{
		temp = get_env_var(env[i]);
		j = 0;
		while (temp[j])
			j++;
		if (env[i][j] == '=')
			printf("%s\n", env[i]);
		free(temp);
	}
}

void	env(char **cmd)
{
    if (ft_strcmp(cmd[0], "env") == 0)
        print_env(shell()->env);
}
