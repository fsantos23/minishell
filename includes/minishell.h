/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:22:38 by fsantos2          #+#    #+#             */
/*   Updated: 2024/03/05 15:22:01 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define PATH_MAX 10000

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <libft.h>
#include <get_next_line.h>
#include <unistd.h>
#include <dirent.h>
#include <signal.h>

typedef enum e_type{
    NONE,
    FD_IN,
    FD_OUT,
    FD_OUT_APP,
    CMD,
    HEREDOC,
    EXPAND,
    BUILTIN 
} t_type ;


typedef struct s_redir {
    t_type type;
    char *str;
    struct s_redir *next;
} t_redir;


typedef struct s_cmd t_cmd;

typedef struct s_cmd {
    char *path;
    char *cmd;
    char **args;
    t_redir *ins;
    t_redir *outs;

    int fd_in;
    int fd_out;
    int	pid;
    int     pip[2];
    
    t_type type;
    
    t_cmd *next;
    t_cmd *prev;
} t_cmd;

typedef struct s_sh {
    bool prompt;
    int status;
    int prev_status;
    int exit_code;
    char **env;
    char *error;
    int lvl;
} t_sh;

t_sh *shell(void);

//----------parsing------------//

void create_list(char *input);
char *organize_input(char *input);
void exec(t_cmd *cmd);
void print_cmd(t_cmd *cmd);
void execute_cmds(t_cmd *cmd);
void print_redir(t_redir *redir);
void    init_shell(void);
void return_error(char *str);
void check_quotes(t_redir *redir);
int execute_redir_all(t_redir *redir);
int check_cmds(t_cmd *cmd);
int close_fd(int in, int out);
void handler(int num);
int error_handler(void);
int check_exit(void);


//----------pipex------------//

char				*ft_strdup_path(char *env, int *x, char *cmd);
void				start_pipex(t_cmd *cmd, char **env);
/* char				*path(t_cmd *cmd, char *env, char *cmds);
 */char				*search_path(char **env, char *cmd);
int					ft_strlen_path(char *env, int x);
void				free_everything(t_cmd *all);
void				execute_path(t_cmd *cmd, char **env);
int					ft_strlen_cmd(char *cmd);
char				*ft_join(char *str, char *delim, char *cmd);
void				return_path(char **env, t_cmd *cmd);
void				free_array(char **str);
void				handle_std(t_cmd *cmd);
void				check_files(char *file, t_cmd *cmd);
void				free_list(t_cmd *cmd);
void				execute(t_cmd *cmd, char **env);
void				check_hd(t_cmd *tmp, t_cmd *cmd);
void				check_args(t_cmd *cmd);

//----------builtins------------//

void execute_builtins(int in, int out, t_cmd *cmd);
void 	pwd(void);
void cd(char **cmd); //
void    put_ls(char *input);
int builtins(char **arg);
void  echo(char **cmd);
char	**get_env(char **envp); //
void export(char **cmd); //
char	**copy_array(char **array);
char	*get_env_var(char *str);
void add_str_to_array(char ***array, char *str);
void  unset(char **cmd); //
char  **rm_str_from_array(char **array, int index);
void update_env(char ***env, char *update);
void	env(char **cmd); //
void	ft_exit(char **cmd);
int	ft_strcmp(char *s1, char *s2);


#endif