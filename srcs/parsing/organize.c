/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:53:43 by fsantos2          #+#    #+#             */
/*   Updated: 2024/02/28 15:32:02 by fsantos2         ###   ########.fr       */
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

int expand(char **input, char *new_input, int *a, t_general *shell)
{
	char *expand;
	char *new;
	int i;
	int b;
	
	i = 0;
	b = 1;
	expand = ft_calloc(sizeof(char), (ft_strlen(*input) * 2));
	while(input[0][b])
	{
		//falta acabar de fazer o $? e tambem falta fazer o unset e o export bem
		if(input[0][1] == '?')
		{
			new = ft_itoa(shell->prev_status);
			printf("new: %s\n", new);
			break ;
		}
		if(input[0][b] == ' ' || input[0][b] == '\"')
			break ;
		expand[i++] = input[0][b++];
	}
	new = getenv(expand);
	if(!new)
	{
		free(new_input);
		shell->status = 1;
		shell->prev_status = 0;
		return 0;
	}
	while(*new)
	{
		new_input[a[0]++] = *new;
		new++;
	}
	input[0] += b;
	return 1;
}

void quote_handle(char *input, t_general *shell)
{
	char *str;
	
	while(1)
	{
		signal(SIGINT, handler);
		write(1, "> ", 2);
		str = get_next_line(STDIN_FILENO);
		if(!ft_strncmp(str, "\"", ft_strlen("\"")))
		{
			free(str);
			break;
		}
		free(str);
	}
	//falta fazer aqui o return do erro e saber qual o erro que da se é se quer que da um erro depois de nao fechar parenteses
	init_shell(shell);
}

char *organize_input(char *input, t_general *shell)
{
	char flag;
	char *new_input;
	int a;

	a = 0;
	flag = 0;
	new_input = ft_calloc(sizeof(char),  (ft_strlen(input) * 3));
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
			if(!expand(&input, new_input, &a, shell))
				return NULL;
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
		quote_handle(input, shell);
	new_input[a] = '\2';
	a++;
	new_input[a] = '\0';
	return new_input;
}
	