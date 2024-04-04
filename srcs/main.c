/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:24:22 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/03 17:03:25 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
            if(input)
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
    if(shell()->error) {
        free(shell()->error);
        shell()->error = NULL;
    }
    if(shell()->env) 
    {
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
