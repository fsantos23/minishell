/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:57:48 by fsantos2           #+#    #+#            */
/*   Updated: 2023/12/25 16:57:48 by fsantos2          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//done

static void	check_sigs(char *cmd)
{
	if (!ft_strncmp(cmd, "./minishell", 11))
	{
		shell()->lvl++;
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, second_handler);
		signal(SIGQUIT, second_handler);
	}
}

static void	execute_cmd(int in, int out, t_cmd *cmd)
{
	check_sigs(cmd->args[0]);
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		printf("fork failed\n");
		exit(EXIT_FAILURE);
	}
	else if (cmd->pid == 0)
	{
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		close_fd(in, out);
		close_fd(cmd->pip[0], cmd->pip[1]);
		execve(cmd->path, cmd->args, shell()->env);
		free_everything(cmd);
		exit(127);
	}
	close_fd(in, out);
}

static int	execute_single_command(int in, int out, t_cmd *cmd)
{
	cmd->fd_in = execute_redir_all(cmd->ins);
	cmd->fd_out = execute_redir_all(cmd->outs);
	if (cmd->fd_in != -1)
		in = cmd->fd_in;
	if (cmd->fd_out != -1)
		out = cmd->fd_out;
	if (cmd->type == BUILTIN)
		execute_builtins(in, out, cmd);
	else
		execute_cmd(in, out, cmd);
	return (cmd->pip[0]);
}

static void	execute_pipe(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		in;
	int		out;

	tmp = cmd;
	in = dup(STDIN_FILENO);
	while (cmd)
	{
		if (cmd->next && pipe(cmd->pip) < 0)
		{
			perror("pipe error");
			exit(EXIT_FAILURE);
		}
		
		out = cmd->pip[1];
		in = execute_single_command(in, out, cmd);
		cmd = cmd->next;
	}
	while (tmp)
	{
		waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
}

void	execute_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	if (!check_cmds(cmd))
		return ;
	execute_pipe(tmp);
}
