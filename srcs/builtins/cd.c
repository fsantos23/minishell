/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:36:39 by fsantos2          #+#    #+#             */
/*   Updated: 2024/02/28 17:54:04 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* void cd(char **cmd, t_general *shell) 
{
  char *temp;
  char **tmp;
  int i;
  int ar_index;
  char cur_dir[10000];
  char **root_dir;

  root_dir = NULL;
  if(!cmd[1])
  {
    getcwd(cur_dir, sizeof(cur_dir));
    root_dir = ft_split(cur_dir, '/');
    root_dir[0] = ft_strjoin("/", root_dir[0]);
    if(chdir(root_dir[0]) != 0)
    {
      perror("error");
      return ;      
    }
  }
  else if(ft_strncmp(cmd[1], "..", ft_strlen(cmd[1])) == 0)
  {
    shell->error = ft_strjoin("not an absolute path: ", cmd[1]);
    shell->status = 1;
    return ;
  }
  else
  {
    char *dir = cmd[1];
    printf("%s\n", dir);
    if(chdir(dir) != 0)
    {
      shell->status = 2;
      shell->error = ft_strjoin("path does not exist: ", cmd[1]);
      return ;      
    }
  }
  update_env(&shell->env, "OLDPWD=");
  update_env(&shell->env, "PWD=");
}
 */

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
        if (!ft_strncmp(tmp, var, ft_strlen(tmp)))
        {
            free(tmp);
            return i;
        }
        free(tmp);
    }
    return -1;
}

void    updt_pwd_var(t_general *shell)
{
    char **ch_env;
    char *pwd;
    char *tmp;

    pwd = get_pwd_env_format();
    ch_env = shell->env;
    if (find_variable(shell->env, "PWD") == -1)
	{
		if (find_variable(ch_env, "OLDPWD") != -1)
			update_env(&ch_env, "OLDPWD");
	}
	else
	{
		if (find_variable(ch_env, "OLDPWD") != -1)
		{
			tmp = ft_strjoin("OLDPWD=",
					&(ch_env)[find_variable(shell->env, "PWD")][4]);
			update_env(&ch_env, tmp);
			free(tmp);
			update_env(&ch_env, pwd);
		}
		else
			update_env(&ch_env, pwd);
	}
    free(pwd);
}

int	cd_home(t_general *shell)
{
	int		i;

	i = find_variable(shell->env, "HOME");
	if (i != -1)
	{
		if (chdir(ft_substr(shell->env[i], 5, ft_strlen(shell->env[i]))) == -1)
		{
			perror("Error:");
			return (-1);
		}
		return (0);
	}
	printf("No VAR HOME available\n");
	return (-1);
}

void cd(char **cmd, t_general *shell)
{
    int i;

    i = 0;
    while (cmd[i])
        i++;
    if (i == 1)
        cd_home(shell);
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
    updt_pwd_var(shell);
}