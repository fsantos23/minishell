/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:42:44 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/03 17:27:23 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	skip_echo_flags(char **cmd, bool *flag)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[++i])
	{
		if (cmd[i][0] != '-')
			return (i);
		j = 1;
		if (cmd[i][1] == '\0')
			return (i);
		while (cmd[i][j])
		{
			if (cmd[i][j] != 'n')
				return (i);
			j++;
		}
		*flag = true;
	}
	return (i);
}

void	echo(char **cmd)
{
	bool	flag;
	int		i;

	flag = false;
	if (!cmd[1])
	{
		printf("\n");
		return ;
	}
	i = skip_echo_flags(cmd, &flag) - 1;
	while (cmd[++i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
	}
	if (!flag)
		printf("\n");
	shell()->exit_code = 0;
}
