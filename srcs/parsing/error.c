/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:12:25 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/12 13:09:58 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//done

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
