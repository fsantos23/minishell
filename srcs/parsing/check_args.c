/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:47:44 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/08 20:02:34 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//done

void	process_redirections(t_cmd *cmd, t_redir *redir, \
t_redir **redir_in_end, t_redir **redir_out_end)
{
	if (redir->type == HEREDOC || redir->type == FD_IN)
	{
		if (*redir_in_end)
			(*redir_in_end)->next = redir;
		else
			cmd->ins = redir;
		*redir_in_end = redir;
	}
	if (redir->type == FD_OUT || redir->type == FD_OUT_APP)
	{
		if (*redir_out_end)
			(*redir_out_end)->next = redir;
		else
			cmd->outs = redir;
		*redir_out_end = redir;
	}
}

t_cmd	*create_cmd(char *str)
{
	int		i;
	t_cmd	*cmd;
	t_redir	*redir;
	t_redir	*redir_in_end;
	t_redir	*redir_out_end;

	i = 0;
	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->args = ft_split(str, '\2');
	redir_in_end = NULL;
	redir_out_end = NULL;
	while (cmd->args[i])
	{
		redir = create_redir(i, cmd);
		if (redir)
		{
			if (!redir->str)
			{
				shell()->error = ft_strdup("syntax error");
				shell()->status = 1;
				return (NULL);
			}
			process_redirections(cmd, redir, &redir_in_end, &redir_out_end);
			i = 0;
		}
		else
			i++;
	}
	return (cmd);
}

t_cmd	*create_tmp(char *args, t_cmd *head)
{
	t_cmd	*tmp;

	if (!args || !iswhitespace(args))
	{
		shell()->error = ft_strdup("syntax error");
		shell()->status = 1;
		if (head)
			free_everything(head);
		return (NULL);
	}
	tmp = create_cmd(args);
	if (!tmp)
		return (NULL);
	tmp->pip[0] = 0;
	tmp->pip[1] = 1;
	tmp->type = cmd_type(tmp->args);
	if (tmp->type == CMD)
		tmp->path = search_path(shell()->env, tmp->args[0]);
	return (tmp);
}

t_cmd	*return_cmd(char **args)
{
	int		i;
	t_cmd	*cmd;
	t_cmd	*head;
	t_cmd	*tmp;

	i = 0;
	head = NULL;
	cmd = NULL;
	tmp = NULL;
	while (args[i])
	{
		tmp = create_tmp(args[i++], head);
		if (!tmp)
			return (NULL);
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
	return (head);
}

void	create_list(char *input)
{
	t_cmd	*cmd;
	char	*arg;
	char	**args;

	arg = organize_input(input);
	if (!arg)
	{
		shell()->status = 1;
		return ;
	}
	args = ft_split(arg, '\3');
	free(arg);
	cmd = return_cmd(args);
	free_array(args);
	if (!cmd)
		return ;
	execute_cmds(cmd);
	free_everything(cmd);
}
