/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:05:26 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/06 07:26:59 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char **normalize(char **args, int size)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < size)
	{
		args[j] = args[i];
		j += args[i] != 0;
		i++;
	}
	return args;
}

t_type get_type(char *str)
{
	if (!str)
		return (NONE);
	if(str[0] == '<' && str[1] == '<' )
		return (HEREDOC);
	if(str[0] == '<' && str[1] == '\0')
		return (FD_IN);
	if(str[0] == '>' && str[1] == '>' )
		return (FD_OUT_APP);
	if(str[0] == '>' && str[1] == '\0')
		return (FD_OUT);
	return (NONE);
}

t_redir *create_redir(int index, t_cmd *cmd)
{
	t_redir *redir;
	t_type  type;
	int i;
	int j;

	i = 0;
	j = 0;
	redir = NULL;
	type = get_type(cmd->args[index]);
	if (type != NONE)
	{
		redir = ft_calloc(1, sizeof(t_redir));
		redir->type = type;
		redir->str = cmd->args[index + 1];
		cmd->args[index] = 0;
		if (cmd->args[index + 1] == NULL)
		{	
			printf("error\n");
			return redir;
		}
		i = index + 2;
		j = index;
		while(cmd->args[i])
			cmd->args[j++] = cmd->args[i++];
		cmd->args[j] = 0;
	}
	return redir;
}
