
// char	**get_env_array(t_data *data)
// {
// 	extern char	**environ;
// 	char		**env_array;
// 	int			i;
// 	int			count;

// 	count = 0;
// 	while (environ[count] != NULL)
// 		count++;
// 	env_array = malloc((count + 1) * sizeof(char *));
// 	if (!env_array)
// 		return (data->status = quitting, NULL);
// 	i = -1;
// 	while (++i < count)
// 	{
// 		env_array[i] = ft_strdup(environ[i]);
// 		if (!env_array[i])
// 		{
// 			free_void_array((void ***)&env_array);
// 			return (data->status = quitting, NULL);
// 		}
// 	}
// 	return (env_array[count] = NULL, env_array);
// }