/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaopereira <joaopereira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:15:51 by joaopereira       #+#    #+#             */
/*   Updated: 2024/02/21 14:48:06 by joaopereira      ###   ########.fr       */
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
	if (!cmd || ft_strcmp(cmd[0], "export") != 0)
		return ;
	if (!cmd[1])
	{
		export = copy_and_alloc(shell()->env);
		print_exp(export);
		free_array(&export);
	}
	else
	{
		while (cmd[++i])
		{
			if (!check_export_conditions(cmd[i]))
			{
				write(STDERR_FILENO, " not a valid identifier\n", 24);
				shell()->exit_code = 1;
			}
			else
				update_env(&shell()->env, cmd[i]);
		}
	}
}
