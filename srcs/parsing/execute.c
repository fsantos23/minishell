/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:57:48 by fsantos2           #+#    #+#             */
/*   Updated: 2023/12/25 16:57:48 by fsantos2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void second_handler(int num)
{
    printf("\n");
}


int close_fd(int in, int out)
{
    if (in != 0)
        close(in);
    if (out != 1)
        close(out);
    return (1);
}

static void execute_cmd(int in, int out, t_cmd *cmd, char **env)
{
    cmd->pid = fork();
    if (cmd->pid < 0)
    {
        printf("fork failed\n");
        exit(EXIT_FAILURE);
    } 
    else if (cmd->pid == 0)
    {
        signal(SIGINT, second_handler);
        dup2(in, STDIN_FILENO);
        dup2(out, STDOUT_FILENO);
        close_fd(in, out);
        close_fd(cmd->pip[0], cmd->pip[1]);
        execve(cmd->path, cmd->args, env);
        free_everything(cmd);
        exit(127);
    }
    close_fd(in, out);
}

static void execute_pipe(t_cmd *cmd, t_general *shell)
{
    t_cmd *tmp = cmd;
    int in;
    int out;

    in = dup(STDIN_FILENO);
    while(cmd)
    {
        if(cmd->next && pipe(cmd->pip) < 0)
        {
            perror("pipe error");
            exit(EXIT_FAILURE);
        }
        cmd->fd_in = execute_redir_all(cmd->ins, shell);
        cmd->fd_out = execute_redir_all(cmd->outs, shell);
        out = cmd->pip[1];
        if (cmd->fd_in != -1)
            in = cmd->fd_in;
        if(cmd->fd_out != -1)
            out = cmd->fd_out;
        if(cmd->type == BUILTIN)
            execute_builtins(in, out, cmd, shell);
        else
            execute_cmd(in, out, cmd, shell->env);
        in = cmd->pip[0];
        cmd = cmd->next;
    }
    while(tmp)
    {
        waitpid(tmp->pid, NULL, 0);
        tmp = tmp->next;
    }
}

void execute_cmds(t_cmd *cmd, t_general *shell)
{
    t_cmd *tmp;

    tmp = cmd;
    check_cmds(cmd, shell);
    execute_pipe(tmp, shell);
}
