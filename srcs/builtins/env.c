/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:30:30 by fsantos2          #+#    #+#             */
/*   Updated: 2024/03/05 14:39:57 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_pwd(char ***env)
{
    char	buf[PATH_MAX + 1];
    char	*cmd;

    getcwd(buf, sizeof(buf));
    cmd = ft_strjoin("PWD=", buf);
    update_env(env, cmd);
    if (find_variable(*env, "OLDPWD") == -1)
        update_env(env, "OLDPWD");
    free(cmd);
}

void	update_shlvl(char ***env, char *value)
{
	char	*shlvl;
	char	*new;

	if (!value)
		return ;
	shlvl = ft_itoa(ft_atoi(value) + 1);
	new = ft_strjoin("SHLVL=", shlvl);
	free(shlvl);
	update_env(env, new);
	free(new);
}

char	**get_env(char **envp)
{
	char	**env;
	char	*var;
	int		i;

	if (!envp)
		return (NULL);
	env = copy_array(envp);
	i = -1;
	while (env[++i])
	{
		var = get_env_var(env[i]);
		if (!ft_strcmp("SHLVL", var))
		{
			update_shlvl(&env, &env[i][ft_strlen(var) + 1]);
			get_pwd(&env);
			free(var);
			return (env);
		}
		free(var);
	}
	update_env(&env, "SHLVL=1");
	get_pwd(&env);
	return (env);
}

void update_env_str(char **str, char *new, char *temp_env, char *temp_cmd)
{
  int env_var;
  int cmd_var;
  int len;

  env_var = ft_strlen(temp_env);
  cmd_var = ft_strlen(temp_cmd);
  if((*str)[env_var] && !new[cmd_var])
    return ;
  len = ft_strlen(*str);
  while (len--)
    (*str)[len + cmd_var] = (*str)[len];

}

void update_env(char ***env, char *new) {
    char **existing_var_split;
    char **new_var_split;
    int i;

    if (!env || !new)
        return;
    new_var_split = ft_split(new, '=');
    i = -1;
    while ((*env)[++i]) {
        existing_var_split = ft_split((*env)[i], '=');

        if (ft_strcmp(existing_var_split[0], new_var_split[0]) == 0)
        {
            if (ft_strchr(new, '=') == NULL)
            {
                free_array(existing_var_split);
                free_array(new_var_split);
                return;
            }
            free((*env)[i]);
            (*env)[i] = ft_strdup(new);
            free_array(existing_var_split);
            free_array(new_var_split);
            return;
        }
        free_array(existing_var_split);
    }
    add_str_to_array(env, new);
    free_array(new_var_split);
}

void	print_env(char	**env)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	while (env && env[++i])
	{
		temp = get_env_var(env[i]);
		j = 0;
		while (temp[j])
			j++;
		if (env[i][j] == '=')
			printf("%s\n", env[i]);
		free(temp);
	}
}

void	env(char **cmd)
{
    if (ft_strcmp(cmd[0], "env") == 0)
        print_env(shell()->env);
}