void  rm_str_from_array(char ***array, int index)
{
  char	**new;
  int	i;
  int	j;

  i = 0;
  j = 0;
  if (!array || !(*array)[index])
    return ;
  while ((*array)[i])
    i++;
  new = malloc(sizeof(char *) * i);
  if (!new)
    return ;
  i = -1;
  while ((*array)[++i])
  {
    if (i != index)
      new[j++] = ft_strdup((*array)[i]);
  }
  new[j] = NULL;
  free_array(*array);
  *array = new;
}

void free_array(char **array)
{
  int i;

  i = -1;
  while (array[++i])
    free(array[i]);
  free(array);
}

void add_str_to_array(char ***array, char *str)
{
  char	**new;
  int	i;

  i = 0;
  if (!array || !str)
    return ;
  while (*array[i])
    i++;
  new = malloc(sizeof(char *) * (i+ 2));
  if (!new)
    return ;
  i = -1;
  while ((*array)[++i])
    new[i] = ft_strdup((*array)[i]);
  new[i++] = ft_strdup(str);
  new[i] = NULL;
  free_array(*array);
  *array = new;
}


char	*get_env_var(char *str)
{
	int		i;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

char	**copy_array(char **array)
{
	char	**new;
	int		i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (array[++i])
		new[i] = ft_strdup(array[i]);
	new[i] = NULL;
	return (new);
}
