/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:53:43 by fsantos2          #+#    #+#             */
/*   Updated: 2024/03/26 15:52:50 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int redir(char **input, char *new_input , int *a)
{
	int i;
	
	i = 0;
	if(input[0][0] == '<' || input[0][0] == '>' || input[0][0] == '|')
	{
		i = 1;
		if(input[0][1] == '<' || input[0][1] == '>')
			i++;
		new_input[a[0]++] = '\2';
		if (input[0][0] == '|')
			input[0][0] = '\3';
		new_input[a[0]++] = input[0][0];
		if (i == 2)
			new_input[a[0]++] = input[0][1];
		new_input[a[0]++] = '\2';
		input[0] += i;
		return 1;
	}
	return 0;
}

static void prev_error(char **input, char *new_input, int *a)
{
	char *new;
	int i;

	i = 0;
	new = ft_itoa(shell()->prev_status);
	while(new[i])
	{
		new_input[a[0]++] = new[i];
		i++;
	}
	input[0] += 2;
}

int expand(char **input, char *new_input, int *a)
{
	char *expand;
	char *new;
	int i;
	int b;
	
	i = 0;
	b = 1;
	new = NULL;
	expand = ft_calloc(sizeof(char), (ft_strlen(*input) * 2));
	while(input[0][b])
	{
		if(input[0][1] == '?')
		{
			prev_error(input, new_input, a);
			free(expand);
			return 1;
		}
		if(input[0][b] == ' ' || input[0][b] == '\"')
			break ;
		expand[i++] = input[0][b++];
	}
	if(!ft_strncmp("$", expand, ft_strlen(expand)))
	{
		free(expand);
		return 0;
	}
	new = getenv(expand);
	free(expand);
	if(!new)
		return 0;
	while(*new)
	{
		new_input[a[0]++] = *new;
		new++;
	}
	input[0] += b;
	return 1;
}

char *organize_input(char *input)
{
	char flag;
	char *new_input;
	int a;

	a = 0;
	flag = 0;
	new_input = ft_calloc(sizeof(char),  (ft_strlen(input) * 50));
	while(*input)
	{
		if((*input == '\"' || *input == '\'') && flag == 0)
		{
			flag = *input;
			input++;
		}
		else if(*input == flag)
		{
			flag = 0;
			input++;
		}
		if(flag != '\'' && *input == '$')
		{
			if(!expand(&input, new_input, &a))
			{
				shell()->error = "command not found";
				free(new_input);
				return NULL;
			}
			continue ;
		}
		if(flag == 0 && redir(&input, new_input, &a) == 1)
			continue ;
		else if(*input == ' ' && flag == 0)
			*input = '\2';
		new_input[a] = *input;
		input++;
		a++;
	}
	if(flag != 0)
	{
		free(new_input);
		shell()->error = "syntax error";
		return NULL;
	}
	new_input[a] = '\2';
	a++;
	new_input[a] = '\0';
	return new_input;
}
	