/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:24:22 by fsantos2          #+#    #+#             */
/*   Updated: 2024/02/28 15:54:19 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void handler(int num)
{
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
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

t_general *create_general(char **env)
{
    t_general *shell;

    shell = ft_calloc(1, sizeof(t_general));
    shell->status = 0;
    shell->prev_status = 0;
    shell->env = env;
    shell->error = ft_calloc(sizeof(char), 100);
    return shell;
}

static void check_exit(t_general *shell)
{
    if(!error_handler(shell))
    {
        free(shell->error);
        init_shell(shell);
    }
    else
    {
        free_array(shell->env);
        free(shell->error);
        free(shell);
        exit(0);
    }
}

void    init_shell(t_general *shell)
{
    char *input;
    
    while(shell->status == 0)
    {
        signal(SIGINT, handler);
        input = readline("msh> ");
        if(!input || !iswhitespace(input))
        {
            if(input)
                free(input);
            init_shell(shell);
        }
        add_history(input);
        create_list(input, shell);
        free(input);
    }
    check_exit(shell);
}

int main(int argc, char **argv, char **env)
{
    (void)argv;
    t_general *shell;

    
    if(argc == 1)
    {
        shell = create_general(env);
        init_shell(shell);
    }
}