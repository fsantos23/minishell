/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:32:19 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/12 13:10:33 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//done

char	*check_cmds(char *cmd)
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
	path = NULL;
	paths = NULL;
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
	{
		shell()->status = 1;
		shell()->error = ft_strdup("env search error");
		return (NULL);
	}
	paths = ft_split(path, ':');
	free(path);
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
		return (check_cmds(cmd));
	paths = search_env(env);
	if (!paths)
		return (NULL);
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
