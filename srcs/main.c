/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:24:22 by fsantos2          #+#    #+#             */
/*   Updated: 2023/11/15 15:55:40 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void init_shell(int argc, char **argv, char **env)
{
    char *input;
    (void)argc;
    (void)argv;
    (void)env;
    
    input = readline("msh> ");
    add_history(input);
    printf("%s\n", input);
    free(input);
}

int main(int argc, char **argv, char **env)
{
    if(argc == 1)
    {
        init_shell(argc, argv, env);
    }
}