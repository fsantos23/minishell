/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:32:59 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/03 14:24:01 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void free_redir(t_redir *redir)
{
	t_redir *tmp;

	while(redir)
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
		if(cmd->type == CMD || cmd->type == BUILTIN)
		{
			free_array(cmd->args);
			if(cmd->path)
				free(cmd->path);
		}
		if(cmd->ins != NULL)
			free_redir(cmd->ins);
		if(cmd->outs != NULL)
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
		i++;
	}
	free(str);
}
