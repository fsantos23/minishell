#include "minishell.h"



void  unset(char **cmd)
{
  char  *temp;
  int   i;
  int   ar_index;
  
  if (!cmd || !cmd[1])
		return ;
  if (cmd[1])
  {
    i = 0;
    while (cmd[++i]) 
    {
      ar_index = -1;
      while (shell()->env[ar_index])
      {
        temp = get_env_var(shell()->env[array_index]);
				if (ft_strcmp(cmd[i], temp) == 0)
				{
					rm_str_from_array(&shell()->env, array_index);
					free(temp);
					break ;
				}
        free(temp);
      }
    }
  }
}
