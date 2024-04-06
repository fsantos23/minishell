/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 17:21:21 by fsantos2           #+#    #+#             */
/*   Updated: 2023/12/23 17:21:21 by fsantos2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int bs(t_redir *cpy)
{
	if (cpy->type == FD_IN && (access(cpy->str, F_OK) != 0))
	{
		(shell()->error = ft_strdup(\
		ft_strjoin("no such file or directory : ", cpy->str)));
		return (0);
	}
    return 1;
}
