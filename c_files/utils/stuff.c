
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


// t_key_value	*init_key_value(char *text)
// {
// 	char		**split;
// 	t_key_value	*key_value;

// 	if (!text)
// 		return (NULL);
// 	key_value = malloc(sizeof(t_key_value));
// 	if (!key_value)
// 		return (NULL);
// 	split = ft_split(text, "=");
// 	if (!split)
// 		return (NULL);
// 	key_value->key = split[0];
// 	key_value->value = split[1];
// 	free(split);
// 	return (key_value);
// }
