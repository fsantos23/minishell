/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:24:22 by fsantos2          #+#    #+#             */
/*   Updated: 2024/03/06 10:30:42 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_sh	*shell(void)
{
	static t_sh	shell;

	return (&shell);
}

int check_exit(void)
{
    if(shell()->status == 0 || shell()->status == 130)
    {
        shell()->prev_status = shell()->status;
        shell()->status = 0;
        return 1;
    }
    if(!error_handler())
    {
        return 1;
    }
    else
    {
        if(shell()->lvl == 0)
            free(shell()->error);
        else
            shell()->lvl--;
        return 0;
    }
}

void handler(int num)
{
    if(num == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        shell()->status = 130;
        check_exit();
    }
    else if(num == SIGQUIT)
    {
        printf("Quit core dumped\n");
    }
}

int iswhitespace(char *input)
{
    int i;

    i = 0;
    while(input[i])
    {
        if(input[i] != ' ')
            return 1;
        i++;
    }
    return 0;
}

void create_general(t_sh *shell, char **env)
{
    shell->status = 0;
    shell->prev_status = 0;
    shell->exit_code = 0;
    shell->env = get_env(env);
    shell->lvl = 0;
    shell->error = ft_calloc(sizeof(char), 100);
}

void    init_shell(void)
{
    char *input;

    shell()->prompt = true;
    while(shell()->prompt == true)
    {
        signal(SIGQUIT, SIG_IGN);
        signal(SIGINT, handler);
        input = readline("msh> ");
        if (!input)
        {
            free(input);
            break ;
        }
        if (!iswhitespace(input))
        {
            if (input)
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

int main(int argc, char **argv, char **env)
{
    (void)argv;

    if(argc == 1)
    {
        create_general(shell(), env);
        init_shell();
    }

    // cleaning up
    if(shell()->error) {
        free(shell()->error);
        shell()->error = NULL;
    }

    if(shell()->env) {
        // Get the size of the environment array
        int i = 0;
        while (shell()->env[i])
        {
            free(shell()->env[i]);
            i++;
        }
        free(shell()->env);
        shell()->env = NULL;
    }

    return (shell()->exit_code);
}
