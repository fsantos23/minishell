/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaopereira <joaopereira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:30:59 by joaopereira       #+#    #+#             */
/*   Updated: 2024/02/28 15:39:20 by joaopereira      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void    updt_pwd_var(void)
{
    char **ch_env;
    char *pwd;
    char *tmp;

    pwd = get_pwd_env_format();
    ch_env = shell->env;
    if (find_var(shell->env, "PWD") == -1)
	{
		if (find_var(ch_env, "OLDPWD") != -1)
			update_env(ch_env, "OLDPWD");
	}
	else
	{
		if (find_var(ch_env, "OLDPWD") != -1)
		{
			tmp = ft_strjoin("OLDPWD=",
					&(ch_env)[find_var(shell->env, "PWD")][4]);
			update_env(ch_env, tmp);
			free(tmp);
			update_env(ch_env, pwd);
		}
		else
			update_env(ch_env, pwd);
	}
    free(pwd);
}

int	cd_home(void)
{
	int		i;

	i = find_variable(shell->env, "HOME");
	if (i != -1)
	{
		if (chdir(shell->env[i][5]) == -1)
		{
			perror("Error:");
			return (-1);
		}
		return (0);
	}
	printf("No VAR HOME available\n");
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
        printf("cd: too many arguments\n");
        return ;
    }
    else
    {
        if (chdir(cmd[1]) == -1)
        {
            perror("Error:");
            return ;
        }
    }
    updt_pwd_var();
}

