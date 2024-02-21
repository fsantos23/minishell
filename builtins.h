/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaopereira <joaopereira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:27:24 by joaopereira       #+#    #+#             */
/*   Updated: 2024/02/21 14:42:02 by joaopereira      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


typedef struct s_sh
{
	bool	prompt;
	bool	error;
	char	**env;
	bool	in_heredoc;
	int		here_fd[2];
	bool	in_exec;
}	t_sh;


t_sh	*shell(void);

void  rm_str_from_array(char ***array, int index);
void free_array(char **array);
void add_str_to_array(char ***array, char *str);
char	*get_env_var(char *str);



void  echo(char **cmd);
int skip_flags(char **cmd, bool *flag);

void  update_env(char ***env, char *new);
void get_pwd(char ***env);
void	update_shlvl(char ***env, char *value);
char	**get_env(char **envp);
void update_env_str(char **str, char *new, char *temp_env, char *temp_cmd);

void	pwd(void);


void	ft_exit(char **cmd);
void  unset(char **cmd)





#endif