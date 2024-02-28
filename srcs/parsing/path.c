/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:32:19 by fsantos2          #+#    #+#             */
/*   Updated: 2024/02/21 20:32:34 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*check_cmd(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

char	**search_env(char **env)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 6) != NULL)
		{
			path = ft_substr(env[i], 6, ft_strlen(env[i]));
			break ;
		}
		i++;
	}
	if (!path)
		perror("env search error\n");
	else
	{
		paths = ft_split(path, ':');
		free(path);
	}
	return (paths);
}

char	*search_path(char **env, char *cmd)
{
	char	**paths;
	char	*part;
	int		i;

	i = 0;
	paths = NULL;
	if (ft_strchr(cmd, '/') != NULL)
		return (check_cmd(cmd));
	paths = search_env(env);
	while (paths[i])
	{
		part = ft_join(paths[i], "/", cmd);
		if (access(part, F_OK) == 0)
		{
			free_array(paths);
			return (part);
		}
		free(part);
		i++;
	}
	free_array(paths);
	return (NULL);
}

char	*ft_join(char *str, char *delim, char *cmd)
{
	char	*tmp;
	char	*new;

	tmp = ft_strjoin(str, delim);
	new = ft_strjoin(tmp, cmd);
	free(tmp);
	return (new);
}
