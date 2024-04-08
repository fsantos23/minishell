/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:58:49 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/08 17:15:33 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	expand_heredoc(char **str, int heredoc[2])
{
	int		i;
	int		a;
	char	*expand_here;
	char	*new;

	new = ft_calloc(sizeof(char), ft_strlen(str[0]));
	i = 0;
	a = 0;
	while (str[0][i])
	{
		if (str[0][i] == '$')
		{
			i++;
			while (ft_isalnum(str[0][i]) && str[0][i] != '_')
				new[a++] = str[0][i++];
			expand_here = expand_env(new);
			write(heredoc[1], expand_here, ft_strlen(expand_here));
			free(expand_here);
		}
		else
			write(heredoc[1], &str[0][i++], 1);
	}
	free(new);
}

void	handle_child_process(t_redir *redir, int heredoc[2], t_cmd *cmd)
{
	char	*str;

	while (1) 
	{
		write(1, "> ", 2);
		signal(SIGINT, handle);
		str = get_next_line(STDIN_FILENO);
		if (shell()->heredoc == 1)
			break ;
		if (!str || (!(ft_strncmp(str, redir->str, ft_strlen(redir->str))) \
		&& ((ft_strlen(str) - 1) == ft_strlen(redir->str))))
		{
			if (!str)
				printf("warning: here-document delimited by end-of-file\n");
			free(str);
			break ;
		}
		expand_heredoc(&str, heredoc);
		free(str);
	}
	close(heredoc[1]);
	free_everything(cmd);
	free_array(shell()->env);
	free(shell()->error);
	exit(shell()->heredoc);
}

int	handle_parent_process(int pid, int heredoc[2])
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
	{
		close(heredoc[0]);
		return (-2);
	}
	close(heredoc[1]);
	return (heredoc[0]);
}

int	execute_heredoc(t_redir *redir, t_cmd *cmd)
{
	int		heredoc[2];
	int		pid;
	char	*expand;

	shell()->heredoc = 0;
	expand = NULL;
	if (pipe(heredoc) < 0) 
	{
		perror("pipe");
		exit(0);
	}
	pid = fork();
	if (pid < 0) 
	{
		printf("fork failed\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		handle_child_process(redir, heredoc, cmd);
	else
	{
		return (handle_parent_process(pid, heredoc));
	}
	return (0);
}
