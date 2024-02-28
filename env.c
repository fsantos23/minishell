

void get_pwd(char ***env)
{
  char	buf[PATH_MAX + 1];
  char	*pwd;

  if (getcwd(buf, sizeof(buf)) != NULL)
  {
    pwd = ft_strjoin("PWD=", buf);
    update_env(env, pwd);
    free(pwd);
  }
  else
    perror("getcwd");
}

void	update_shlvl(char ***env, char *value)
{
	char	*shlvl;
	char	*new;

	if (!value)
		return ;
	shlvl = ft_itoa(ft_atoi(value) + 1);
	new = ft_strjoin("SHLVL=", shlvl);
	free(shlvl);
	update_env(env, new);
	free(new);
}

char	**get_env(char **envp)
{
	char	**env;
	char	*var;
	int		i;

	if (!envp)
		return (NULL);
	env = copy_array(envp);
	i = -1;
	while (env[++i])
	{
		var = get_env_var(env[i]);
		if (!ft_strcmp("SHLVL", var))
		{
			update_shlvl(&env, &env[i][ft_strlen(var) + 1]);
			get_pwd(&env);
			free(var);
			return (env);
		}
		free(var);
	}
	update_env(&env, "SHLVL=1");
	get_pwd(&env);
	return (env);
}

void update_env_str(char **str, char *new, char *temp_env, char *temp_cmd)
{
  int env_var;
  int cmd_var;
  int i;
  int len;

  env_var = ft_strlen(temp_env);
  cmd_var = ft_strlen(temp_cmd);
  if((*str)[env_var] && !new[cmd_var])
    return ;
  len = ft_strlen(*str);
  while (len--)
    (*str)[len + cmd_var] = (*str)[len];
  
}

void  update_env(char ***env, char *new)
{
  char	*var;
  int	i;

  if (!env || !new)
    return ;
  i = -1;
  while ((*env)[++i])
  {
    var = get_env_var((*env)[i]);
    if (!ft_strcmp(var, new))
    {
      free(var);
      free((*env)[i]);
      (*env)[i] = ft_strdup(new);
      return ;
    }
    free(var);
  }
  *env = add_str_to_array(*env, new);
}

void	print_env(char	**env)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	while (env && env[++i])
	{
		temp = get_env_var(env[i]);
		j = 0;
		while (temp[j])
			j++;
		if (env[i][j] == '=')
			printf("%s\n", env[i]);
		free(temp);
	}
}

void	env(char **cmd)
{
	if (ft_strcmp(cmd[0], "env") == 0)
		print_env(shell->env);
}
