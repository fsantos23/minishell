/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:26:51 by fsantos2          #+#    #+#             */
/*   Updated: 2024/02/28 17:04:29 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pwd(void)
{
	char	buf[PATH_MAX + 1];

	if (getcwd(buf, sizeof(buf)) != NULL)
		printf("%s\n", buf);
	else
		perror("getcwd");
}