/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:50:17 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/07 22:28:39 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_exit(char **cmd)
{
	int	i;

	i = -1;
	while (cmd && cmd[1] && cmd[1][++i])
	{
		if (i == 0 && (cmd[1][0] == '+' || cmd[1][0] == '-'))
			continue ;
		else if (!ft_isdigit(cmd[1][i]))
		{
			shell()->error = ft_strdup("Exit: numeric argument required");
			shell()->status = 1;
			return ;
		}
		else if (cmd[1][i + 1] == '\0' && cmd[2])
		{
			shell()->error = ft_strdup("Exit: too many arguments");
			shell()->status = 1;
			return ;
		}
		else if (cmd[1][i + 1] == '\0')
			shell()->exit_code = ft_atoi(cmd[1]);
	}
	shell()->prompt = false;
}
