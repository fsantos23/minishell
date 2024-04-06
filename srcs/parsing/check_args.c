/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:47:44 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/06 08:09:29 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


t_type	cmd_type(char **arg)
{
	t_type type;
	
	if(!builtins(arg))
		type = CMD;
	else
		type = BUILTIN;
	return type;
}

void put_redit_to_list(t_redir *type, t_cmd *cmd, t_redir *redir)
{
	if (!type)
		type->next = redir;
	else
	{
		if (redir->type == HEREDOC || redir->type == FD_IN)
			cmd->ins = redir;
		else if (redir->type == FD_OUT || redir->type == FD_OUT_APP)
			cmd->outs = redir;
	}
	type = redir;
}

t_cmd	*create_cmd(char *str)
{
	int i;
	t_cmd *cmd;
	t_redir *redir;
	t_redir *redir_in_end;
	t_redir *redir_out_end;
	
	i = 0;
	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->args = ft_split(str, '\2');
	redir_in_end = NULL;
	redir_out_end = NULL;
	while (cmd->args[i])
	{
		redir = create_redir(i, cmd);
		//encontrar esta função
		if (redir)
		{
			if (redir->type == HEREDOC || redir->type == FD_IN)
			{
				if (redir_in_end)
					redir_in_end->next = redir;
				else
					cmd->ins = redir;
				redir_in_end = 	redir;
			}
			if (redir->type == FD_OUT || redir->type == FD_OUT_APP)
			{
				if (redir_out_end)
					redir_out_end->next = redir;
				else
					cmd->outs = redir;
				redir_out_end = redir;
			}
			i = 0;
		}
		else
			i++;
	}
	return cmd;
}

t_cmd	*create_tmp(char *args, t_cmd *head)
{
	t_cmd *tmp;
	
	if (!args || !iswhitespace(args))
	{
		shell()->error = ft_strdup("syntax error");
		shell()->status = 1;
		if (head)
			free_everything(head);
		return NULL;
	}
	tmp = create_cmd(args);
	tmp->pip[0] = 0;
	tmp->pip[1] = 1;
	tmp->path = search_path(shell()->env, tmp->args[0]);
	tmp->type = cmd_type(tmp->args);
	return tmp;
}

t_cmd	*return_cmd(char **args)
{
	int i;
	t_cmd *cmd;
	t_cmd *head;
	t_cmd *tmp;

	i = 0;
	head = NULL;
	cmd = NULL;
	tmp = NULL;
	while (args[i])
	{
		tmp = create_tmp(args[i++], head);
		if (!tmp)
			return NULL;
		if (!head)
			head = tmp;
		else
		{
			cmd = head;
			while (cmd->next != NULL)
				cmd = cmd->next;
			cmd->next = tmp;
		}
	}
	return head;
}

int	check_ins(t_redir *redir)
{
	t_redir *cpy;
	struct stat status;

	cpy = redir;
	while (cpy)
	{
		if (cpy->type == FD_IN && access(cpy->str, F_OK) != 0)
		{
			shell()->error = ft_strdup(ft_strjoin("no such file or directory : ", cpy->str));
			return 0;
		}
		if (cpy->type == FD_IN && access(cpy->str, R_OK) != 0)
		{
			shell()->error = ft_strdup(ft_strjoin("can't read that file : ", cpy->str));
			return 0;
		}
		if (cpy->type == FD_IN && stat(cpy->str, &status) != -1 && S_ISDIR(status.st_mode))
		{
			shell()->error = ft_strdup(ft_strjoin("is a directory : ", cpy->str));
			return 0;
		}
		cpy = cpy->next;
	}
	return 1;
}

void create_list(char *input)
{
	t_cmd *cmd;
	char *arg; 
	char **args;

	arg = organize_input(input);
	if(!arg)
	{
		shell()->status = 1;
		return ;
	}
	args = ft_split(arg, '\3');
	free(arg);
	cmd = return_cmd(args);
	free_array(args);
	if(!cmd)
		return ;
	if(check_ins(cmd->ins))
		execute_cmds(cmd);
	else
		shell()->status = 1;
	free_everything(cmd);
}
