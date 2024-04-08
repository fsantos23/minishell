/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:53:43 by fsantos2          #+#    #+#             */
/*   Updated: 2024/04/08 11:18:17 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//done

static int	redir(char **input, char *new_input, int *a)
{
	int	i;

	i = 0;
	if (input[0][0] == '<' || input[0][0] == '>' || input[0][0] == '|')
	{
		i = 1;
		if (input[0][1] == '<' || input[0][1] == '>')
			i++;
		new_input[a[0]++] = '\2';
		if (input[0][0] == '|')
			input[0][0] = '\3';
		new_input[a[0]++] = input[0][0];
		if (i == 2)
			new_input[a[0]++] = input[0][1];
		new_input[a[0]++] = '\2';
		input[0] += i;
		return (1);
	}
	return (0);
}

int	itenerate_input(char **input, char **expand, \
char *new_input, int *a)
{
	int	i;
	int	b;

	i = 0;
	b = 1;
	if (ft_isdigit(input[0][b]))
		return (1);
	while (input[0][b])
	{
		if (input[0][1] == '?')
		{
			prev_error(input, new_input, a);
			return (0);
		}
		if (!ft_isalnum(input[0][b]) && input[0][b] != '_')
			break ;
		expand[0][i++] = input[0][b++];
	}
	return (b);
}

void	expand(char **input, char *new_input, int *a)
{
	char	*expand;
	char	*new;
	int		b;
	int		i;

	i = 0;
	b = 0;
	new = NULL;
	expand = ft_calloc(sizeof(char), (ft_strlen(*input) * 2));
	b = itenerate_input(input, &expand, new_input, a);
	if (b == 0)
	{
		free(expand);
		return ;
	}
	new = expand_env(expand);
	free(expand);
	if (!new)
		return ;
	while (new[i])
		new_input[a[0]++] = new[i++];
	free(new);
	input[0] += b;
}

void	process_character(char *input, char *new_input, int *a, char *flag)
{
	while (*input)
	{
		if ((*input == '\"' || *input == '\'') && flag[0] == 0)
		{
			flag[0] = *input;
			input++;
		}
		else if (flag[0] == *input)
		{
			flag[0] = 0;
			input++;
		}
		else if (flag[0] != '\'' && *input == '$' && input[1])
			expand(&input, new_input, a);
		else if (flag[0] == 0 && redir(&input, new_input, a))
			continue ;
		else if (*input == ' ' && flag[0] == 0)
			*input = '\2';
		if (*input)
			new_input[a[0]++] = *input++;
	}
}

char	*organize_input(char *input)
{
	char	flag;
	char	*new_input;
	int		a;

	a = 0;
	flag = 0;
	new_input = ft_calloc(sizeof(char), (ft_strlen(input) * 100));
	process_character(input, new_input, &a, &flag);
	if (flag != 0)
	{
		free(new_input);
		shell()->error = ft_strdup("syntax error");
		return (NULL);
	}
	new_input[a++] = '\2';
	new_input[a] = '\0';
	return (new_input);
}
