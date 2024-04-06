/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:41:49 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/06 15:15:10 by fsantos2         ###   ########.fr       */
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
    if((shell()->status == 0 || shell()->status == 130) && shell()->exit_code == -1)
    {
        shell()->prev_status = shell()->status;
        shell()->status = 0;
        return 1;
    }
    if(!error_handler())
        return 1;
    else if(shell()->exit_code != -1)
    {
        if(shell()->error)
        {
            printf("%s\n", shell()->error);
            free(shell()->error);
        }
        shell()->lvl--;
        return 0;
    }
    return 0;
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

int size_args(char **args)
{
	int i;

	i = 0;
	while(args[i])
		i++;
	return i;
}

int close_fd(int in, int out)
{
    if (in != 0)
        close(in);
    if (out != 1)
        close(out);
    return (1);
}
