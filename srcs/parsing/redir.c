/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:53:32 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/08 17:10:27 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//done

void	handle(int num)
{
	if (num == SIGINT)
	{
		shell()->heredoc = 1;
		close(STDIN_FILENO);
	}
}

int	execute_infile(t_redir *redir)
{
	int	fd_in;

	if (!check_ins(redir))
		return (-2);
	fd_in = open(redir->str, O_RDONLY);
	if (fd_in < 0)
		return (0);
	return (fd_in);
}

int	execute_to_outfile(t_redir *redir)
{
	int	fd_out;

	if (!check_out(redir))
		return (-2);
	if (redir->type == FD_OUT_APP)
		fd_out = open(redir->str, O_RDWR | O_CREAT | O_APPEND, 0777);
	else
		fd_out = open(redir->str, O_RDWR | O_CREAT | O_TRUNC, 0777);
	return (fd_out);
}

int	execute_redir_all(t_redir *redir, t_cmd *cmd)
{
	int	fd;

	fd = -1;
	while (redir)
	{
		if (fd != -1 && fd != -2)
			close(fd);
		if (redir->type == FD_IN)
			fd = execute_infile(redir);
		else if (redir->type == HEREDOC)
			fd = execute_heredoc(redir, cmd);
		else
			fd = execute_to_outfile(redir);
		if (fd < 0)
			break ;
		redir = redir->next;
	}
	return (fd);
}
