/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:12:25 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/07 19:15:37 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//done

int	check_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (!tmp->path && tmp->type == CMD)
		{
			(shell()->error = ft_strjoin(tmp->args[0], " : command not found"));
			shell()->status = 127;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	error_handler(void)
{
	shell()->prev_status = shell()->status;
	if (shell()->error)
	{
		printf("%s\n", shell()->error);
		free(shell()->error);
		shell()->error = NULL;
	}
	shell()->status = 0;
	return (0);
}
