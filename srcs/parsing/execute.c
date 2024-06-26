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

void close_all(int index)
{
	while (index <= FOPEN_MAX)
	{
		close(index);
		index++;
	}
}

static void	check_sigs(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void check_cmd(t_cmd *cmd)
{
	struct stat st;

	lstat(cmd->args[0], &st);
	if (S_ISDIR(st.st_mode))
		write(2, "Is a directory\n", 15);
	else if (!cmd->path)
	{
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": command not found\n", 20);
	}
	else
	{
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": command not found\n", 20);
	}
}

static void	execute_cmd(int in, int out, t_cmd *cmd)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		printf("fork failed\n");
		exit(EXIT_FAILURE);
	}
	else if (cmd->pid == 0)
	{

		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		close_fd(in, out);
		close_fd(cmd->pip[0], cmd->pip[1]);
		if (cmd->path)
			execve(cmd->path, cmd->args, shell()->env);
		check_cmd(cmd);
		free_everything(cmd);
		free(shell()->error);
		free_array(shell()->env);
		exit(127);
	}
	close_fd(in, out);
}

static int	execute_single_command(int in, int out, t_cmd *cmd)
{
	cmd->fd_in = in;
	cmd->fd_out = out;
	cmd->fd_in = execute_redir_all(cmd->ins, cmd);
	cmd->fd_out = execute_redir_all(cmd->outs, cmd);
	if (cmd->fd_in == -2 || cmd->fd_out == -2) {
		close_fd(in, out);
		close_fd(-2, cmd->pip[1]);
		return (cmd->pip[0]);
	}
	if (cmd->fd_out != -1 && cmd->fd_out != -2) {
		close_fd(-2, out);
		out = cmd->fd_out;
	}
	if (cmd->fd_in != -1 && cmd->fd_in != -2) {
		close_fd(in, -2);
		in = cmd->fd_in;
	}
	if (cmd->type == BUILTIN)
		execute_builtins(in, out, cmd);
	else if (cmd->type == CMD)
		execute_cmd(in, out, cmd);
	else if (cmd->type == NONE && cmd->ins)
	{
		close_fd(-2, cmd->pip[1]);
		close_fd(in, out);
	}
	return (cmd->pip[0]);
}

static void	execute_pipe(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		in;
	int		out;

	tmp = cmd;
	in = dup(STDIN_FILENO);
	check_sigs();
	while (cmd)
	{
		create_pipe(cmd);
		out = cmd->pip[1];
		in = execute_single_command(in, out, cmd);
		cmd = cmd->next;
	}
	while (tmp)
	{
		handle_wait_child(tmp);
		tmp = tmp->next;
	}
	close_all(3);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}

void	execute_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	execute_pipe(tmp);
}
