/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:32:59 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/12 12:25:10 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//done

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		free(redir->str);
		tmp = redir;
		redir = redir->next;
		free(tmp);
	}
}

void	free_everything(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		if (cmd->type == CMD || cmd->type == BUILTIN)
		{
			if (cmd->path)
				free(cmd->path);
		}
		free_array(cmd->args);
		if (cmd->ins != NULL)
			free_redir(cmd->ins);
		if (cmd->outs != NULL)
			free_redir(cmd->outs);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

void	free_list(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

void	free_array(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
        str[i] = NULL;
		i++;
	}
	free(str);
    str = NULL;
}

void	free_array2(char ***array)
{
    int		i;
    int		len;

    if (!(*array))
        return ;
    len = 0;
    while ((*array)[len])
        len++;
    i = -1;
    while (++i < len)
        free((*array)[i]);
    free((*array));
}
