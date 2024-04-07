/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ext.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:55:25 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/07 15:00:07 by fsantos2         ###   ########.fr       */
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
