/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:54:25 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/07 20:06:10 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//done

void	prev_error(char **input, char *new_input, int *a)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_itoa(shell()->prev_status);
	while (new[i])
	{
		new_input[a[0]++] = new[i];
		i++;
	}
	free(new);
	input[0] += 2;
}

char	*expand_env(char *expand)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (shell()->env[i])
	{
		if (!ft_strncmp(shell()->env[i], expand, ft_strlen(expand)))
		{
			new = ft_substr(shell()->env[i], ft_strlen(expand) + 1, \
			ft_strlen(shell()->env[i]));
			return (new);
		}
		i++;
	}
	return (new);
}
