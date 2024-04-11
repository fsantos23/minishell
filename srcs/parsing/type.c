/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 17:21:21 by fsantos2           #+#    #+#            */
/*   Updated: 2023/12/23 17:21:21 by fsantos2          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//done

int	bs(t_redir *cpy)
{
	if (cpy->type == FD_IN && (access(cpy->str, F_OK) != 0))
	{
		(shell()->error = ft_strjoin("no such file or directory : ", cpy->str));
		shell()->status = 1;
		return (0);
	}
	return (1);
}

void	second_handler(int num)
{
	if (num == SIGINT)
	{
		shell()->status = 130;
		printf("\n");
	}
	else if (num == SIGQUIT)
		printf("Quit core dumped\n");
}

int	check_out(t_redir *out)
{
	t_redir	*cpy;

	cpy = out;
	if (access(cpy->str, F_OK) != 0)
	{
		cpy = cpy->next;
		return (1);
	}
	if (access(cpy->str, F_OK) == 0 && (access(cpy->str, W_OK) != 0))
	{
		(shell()->error = ft_strjoin("can't write to that file : ", cpy->str));
		shell()->status = 1;
		return (0);
	}
	return (1);
}


int	is_justredir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '>' && str[i] != '<' && str[i] != ' ' && str[i] != '\n' && str[i] != '\2')
			return (1);
		i++;
	}
	return (0);
}
