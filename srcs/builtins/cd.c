/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:36:39 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/03 17:00:59 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *get_pwd_env_format(void)
{
    char buf[PATH_MAX + 1];
    char *cmd;

    if (getcwd(buf, sizeof(buf)) == NULL)
    {
        perror("getcwd");
        return NULL;
    }

    cmd = ft_strjoin("PWD=", buf);
    if (!cmd)
    {
        perror("ft_strjoin");
        return NULL;
    }

    return cmd;
}

int find_variable(char **env, char *var)
{
    char *tmp;
    int i;

    i = -1;
    while(env[++i])
    {
        tmp = get_env_var(env[i]);
        if (!ft_strcmp(tmp, var))
        {
            free(tmp);
            return i;
        }
        free(tmp);
    }
    return -1;
}

void    updt_pwd_var()
{
    char **ch_env;
    char *pwd;
    char *tmp;

    pwd = get_pwd_env_format();
    ch_env = shell()->env;
    if (find_variable(shell()->env, "PWD") == -1)
	{
		if (find_variable(ch_env, "OLDPWD") != -1)
			update_env(&ch_env, "OLDPWD");
	}
	else
	{
		if (find_variable(ch_env, "OLDPWD") != -1)
		{
			tmp = ft_strjoin("OLDPWD=",&(ch_env)[find_variable(shell()->env, "PWD")][4]);
			update_env(&ch_env, tmp);
			free(tmp);
			update_env(&ch_env, pwd);
		}
		else
			update_env(&ch_env, pwd);
	}
    free(pwd);
}

int	cd_home(void)
{
    int		i;

    i = find_variable(shell()->env, "HOME");
    if (i != -1)
    {
        if (chdir(&shell()->env[i][5]) == -1)
        {
            perror("Error:");
            shell()->exit_code = 1;
            return (-1);
        }
        return (0);
    }
    printf("var Home disabled\n");
    return (-1);
}

void cd(char **cmd)
{
    int i;

    i = 0;
    while (cmd[i])
        i++;
    if (i == 1)
        cd_home();
    else if (i > 2)
    {
        write(STDERR_FILENO, " too many arguments\n", 20);
        shell()->exit_code = 1;
        return ;
    }
    else
    {
        if (chdir(cmd[1]) == -1)
        {
            perror("Error");
            shell()->exit_code = 1;
            return ;
        }
    }
    updt_pwd_var();
    shell()->exit_code = 0;
}
