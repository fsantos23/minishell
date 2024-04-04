/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:05:26 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/03 17:06:27 by fsantos2         ###   ########.fr       */
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

void print_cmd(t_cmd *cmd)
{
	int i = 0;

	if (cmd)
	{
		printf("cmd->cmd: %s\n", cmd->cmd);
		printf("cmd->cmd_args: %s\n", cmd->args[0]);
		/* printf("cmd->in_file: %s\n", cmd->in_file); */
		/* printf("cmd->out_file: %s\n", cmd->out_file); */
		/* printf("cmd->heredoc: %s\n", cmd->heredoc); */
		printf("cmd->cmd_type: %d\n", cmd->type);
		printf("cmd->path: %s\n", cmd->path);
		i = 0;
		printf("herererrererer \n");
		if(cmd->ins)
		{
			printf("ins: %s\n", cmd->ins->str);
		}
		while(cmd->args[i])
		{
			printf("cmd->cmd_args[%d]: %s\n", i, cmd->args[i]);
			i++;
		}
		printf("----------------------------------------------------------------------------------------\n");
	}
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

void print_redir(t_redir *redir)
{
	printf("======redir=====\n");
	printf("type: %d\n", redir->type);
	printf("arg: %s\n", redir->str);
}