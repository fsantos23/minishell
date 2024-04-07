/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:30:30 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/07 14:45:41 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	update_var(char ***env, char *new, char **ex_var, int index)
{
	char	*dup_new;

	dup_new = NULL;
	if (ft_strchr(new, '=') != NULL)
	{
		dup_new = ft_strdup(new);
		free((*env)[index]);
		(*env)[index] = dup_new;
	}
	free_array(ex_var);
}

void	update_env(char ***env, char *new)
{
	char	**existing_var;
	char	**new_var;
	int		i;

	if (!env || !new)
		return ;
	new_var = ft_split(new, '=');
	i = -1;
	while ((*env)[++i])
	{
		existing_var = ft_split((*env)[i], '=');
		if (ft_strcmp(existing_var[0], new_var[0]) == 0)
		{
			update_var(env, new, existing_var, i);
			free_array(new_var);
			return ;
		}
		free_array(existing_var);
	}
	add_str_to_array(env, new);
	free_array(new_var);
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
