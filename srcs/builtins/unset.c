/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:55:19 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/08 16:35:41 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	unset(char **cmd)
{
	char	*temp;
	int		i;
	int		ar_index;

	i = 0;
	while (cmd[++i])
	{
		ar_index = -1;
		while (shell()->env[++ar_index])
		{
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
