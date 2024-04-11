/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:24:22 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/09 17:35:39 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//done

int	iswhitespace(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '\2')
			return (1);
		i++;
	}
	return (0);
}

void	create_general(t_sh *shell, char **env)
{
	shell->status = 0;
	shell->prev_status = 0;
	shell->env = get_env(env);
	shell->lvl = 0;
	shell->error = NULL;
	shell->heredoc = 0;
}

void	init_shell(void)
{
	char	*input;

	shell()->prompt = true;
	while (shell()->prompt == true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler);
		input = readline("msh> ");
		if (!input)
			break ;
		if (!iswhitespace(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		create_list(input);
		free(input);
		if (!check_exit())
			break ;
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **env)
{
	(void) argv;
	if (argc == 1)
	{
		create_general(shell(), env);
		init_shell();
		printf("exit\n");
		free_array(shell()->env);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		return (shell()->exit_code);
	}
	return (0);
}
