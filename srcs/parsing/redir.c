/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:53:32 by fsantos2          #+#    #+#             */
/*   Updated: 2024/02/28 00:40:09 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


static int	execute_infile(t_redir *redir, t_general *shell)
{
    int fd_in;
    
	fd_in = open(redir->str, O_RDONLY, 0777);
    return fd_in;
}

static int	execute_heredoc(t_redir *redir)
{
	char	*str;
	int fd;

	//falta perceber o que se passa com heredoc ele abre e escreve tudo bem mas depois nao envia a informação para o file expecificado
    fd = open("/tmp/temp", O_CREAT | O_RDWR | O_TRUNC, 0777);
	str = NULL;
	while (1)
	{
		write(1, "> ", 2);
		str = get_next_line(STDIN_FILENO);
		if (!(ft_strncmp(str, redir->str, ft_strlen(redir->str))) && ((ft_strlen(str)- 1) == ft_strlen(redir->str)))
		{
			free(str);
			break ;
		}
		write(fd, str, ft_strlen(str));
		free(str);
	}
    return fd;
}

static int	execute_to_outfile(t_redir *redir)
{
    int fd_out;
    
	if(redir->type == FD_OUT_APP)
		fd_out = open(redir->str, O_RDWR | O_CREAT | O_APPEND, 0777);
	else
		fd_out = open(redir->str, O_RDWR | O_CREAT | O_TRUNC, 0777);
    return fd_out;
}

int execute_redir_all(t_redir *redir, t_general *shell)
{
    int in_out;
    
    in_out = -1;
    while(redir)
    {
        close(in_out);
        if(redir->type == FD_IN)
            in_out = execute_infile(redir, shell);
        else if(redir->type == HEREDOC)
            in_out = execute_heredoc(redir);
        else
            in_out = execute_to_outfile(redir);
        redir = redir->next;
    }
    return (in_out);
}