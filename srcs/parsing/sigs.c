/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:40:18 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/08 17:02:07 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_wait_child(t_cmd *cmd)
{
	int	buffer;

	if (cmd->pid == 0)
		return ;
	waitpid(cmd->pid, &buffer, 0);
	if (WIFEXITED(buffer))
		shell()->status = WEXITSTATUS(buffer);
	else if (WIFSIGNALED(buffer))
	{
		shell()->status = WTERMSIG(buffer) + 128;
		if (WTERMSIG(buffer) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(buffer) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
	}
}

void	create_pipe(t_cmd *cmd)
{
	if (cmd->next && pipe(cmd->pip) < 0)
	{
		perror("pipe error");
		exit(EXIT_FAILURE);
	}
}
