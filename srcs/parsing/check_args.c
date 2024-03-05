/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:47:44 by fsantos2          #+#    #+#             */
/*   Updated: 2024/03/05 15:00:20 by fsantos2         ###   ########.fr       */
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

int size_args(char **args)
{
	int i;

	i = 0;
	while(args[i])
		i++;
	return i;
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
	if(check_ins(cmd->ins) && check_ins(cmd->outs))
		execute_cmds(cmd);
	free_everything(cmd);
}
