/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:53:32 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/07 20:09:01 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//done

int	execute_infile(t_redir *redir)
{
	int	fd_in;

	fd_in = open(redir->str, O_RDONLY);
	if (fd_in < 0)
		return (0);
	return (fd_in);
}

int	execute_heredoc(t_redir *redir)
{
	char	*str;
	int		heredoc[2];

	if (pipe(heredoc) < 0)
	{
		perror("pipe");
		exit(0);
	}
	str = NULL;
	while (1)
	{
		write(1, "> ", 2);
		str = get_next_line(STDIN_FILENO);
		if (!(ft_strncmp(str, redir->str, ft_strlen(redir->str))) \
		&& ((ft_strlen(str) - 1) == ft_strlen(redir->str)))
		{
			free(str);
			break ;
		}
		write(heredoc[1], str, ft_strlen(str));
		free(str);
	}
	close(heredoc[1]);
	return (heredoc[0]);
}

int	execute_to_outfile(t_redir *redir)
{
	int	fd_out;

	if (redir->type == FD_OUT_APP)
		fd_out = open(redir->str, O_RDWR | O_CREAT | O_APPEND, 0777);
	else
		fd_out = open(redir->str, O_RDWR | O_CREAT | O_TRUNC, 0777);
	return (fd_out);
}

int	execute_redir_all(t_redir *redir)
{
	int	fd;

	fd = -1;
	while (redir)
	{
		if (fd != -1)
			close(fd);
		if (redir->type == FD_IN)
			fd = execute_infile(redir);
		else if (redir->type == HEREDOC)
			fd = execute_heredoc(redir);
		else
			fd = execute_to_outfile(redir);
		redir = redir->next;
	}
	return (fd);
}
