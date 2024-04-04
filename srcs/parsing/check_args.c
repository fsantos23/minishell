/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:47:44 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/03 17:04:41 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


t_type cmd_type(char **arg)
{
	t_type type;
	
	if(!builtins(arg))
		type = CMD;
	else
		type = BUILTIN;
	return type;
}

t_cmd *create_cmd(char *str)
{
	int i = 0;
	t_cmd *cmd;
	t_redir *redir;
	t_redir *redir_in_end;
	t_redir *redir_out_end;

	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->args = ft_split(str, '\2');
	cmd->pip[0] = 0;
	cmd->pip[1] = 1;
	redir_in_end = NULL;
	redir_out_end = NULL;
	while (cmd->args[i])
	{
		redir = create_redir(i, cmd);
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

t_cmd *return_cmd(char **args, char **env)
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
		tmp = create_cmd(args[i++]);
		tmp->path = search_path(env, tmp->args[0]);
		tmp->type = cmd_type(tmp->args);
		if(!head)
			head = tmp;
		else
		{
			cmd = head;
			while(cmd->next != NULL)
				cmd = cmd->next;
			cmd->next = tmp;
		}
	}
	return head;
}

int check_ins(t_redir *redir)
{
	t_redir *cpy;
	struct stat status;

	cpy = redir;
	while(cpy)
	{
		if(cpy->type != HEREDOC)
		{
			if(access(cpy->str, F_OK) != 0)
			{
				shell()->status = 1;
				shell()->error = ft_strjoin("no such file or directory : ", cpy->str);
				return 0;
			}
			if(access(cpy->str, R_OK) != 0)
			{
				shell()->status = 1;
				shell()->error = ft_strjoin("can't read that file : ", cpy->str);
				return 0;
			}
			if((cpy->type == FD_OUT || cpy->type == FD_OUT_APP) && access(cpy->str, R_OK) != 0)
			{
				shell()->status = 1;
				shell()->error = ft_strjoin("can't read that file : ", cpy->str);
				return 0;
			}
			if(stat(cpy->str, &status) == -1)
				perror("stat\n");
			if(S_ISDIR(status.st_mode))
			{
				shell()->status = 1;
				shell()->error = ft_strjoin("is a directory : ", cpy->str);
				return 0;
			}			
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
		free(arg);
		printf("%s\n", shell()->error);
		check_exit();
		return ;
	}
	args = ft_split(arg, '\3');
	free(arg);
	cmd = return_cmd(args, shell()->env);
	free_array(args);
	//falta só atualizar o check_ins, ou seja, as permissoes para os files 
	if(check_ins(cmd->ins) && check_ins(cmd->outs))
		execute_cmds(cmd);
	free_everything(cmd);
}
