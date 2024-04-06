/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:57:53 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/06 03:31:22 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_export_conditions(char *str)
{
	int	i;

	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 0;
	while (str[++i] && str[i] != '=')
	{
		if (!(ft_isalpha(str[i]) || ft_isdigit(str[i] || str[i] == '_')))
			return (0);
	}
	return (1);
}

char	**copy_and_alloc(char **array)
{
	char	**new;
	char	*temp;
	int		i;
	int		j;

	new = copy_array(array);
	i = -1;
	while (new && new[++i] && new[i + 1])
	{
		j = -1;
		while (new && new[++j] && new[j + 1])
		{
			if (ft_strcmp(new[j], new[j + 1]) > 0)
			{
				temp = new[j];
				new[j] = new[j + 1];
				new[j + 1] = temp;
			}
		}
	}
	return (new);
}

void	print_exp(char **sorted_env)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	while (sorted_env[++i])
	{
		temp = get_env_var(sorted_env[i]);
		if (ft_strcmp(temp, "_") != 0)
		{
			printf("declare -x %s", temp);
			j = 0;
			while (temp[j])
				j++;
			if (sorted_env[i][j] == '=')
				printf("=\"%s\"\n", &sorted_env[i][j + 1]);
			else
				printf("\n");
		}
		free(temp);
	}
}

void export(char **cmd)
{
	char **export;
	int i;

	i = 0;
	if (!cmd[1])
	{
		export = copy_and_alloc(shell()->env);
		print_exp(export);
		free_array(export);
	}
	else
	{
		while (cmd[++i])
		{
			if (!check_export_conditions(cmd[i]))
			{
				shell()->error = ft_strdup("not a valid identifier");
				shell()->status = 2;
				return ;
			}
			else {
                update_env(&shell()->env, cmd[i]);
            }
		}
	}
}
