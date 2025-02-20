/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:04:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/19 22:47:17 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	g_quit_in_heredoc = 0;

static int	handle_args(t_data *d, char *argv[])
{
	char		*script;
	char		**args;
	t_dblist	*args_list;

	(void)env;
	args = NULL;
	script = ft_megajoin(d->cwd, "/", argv[1], NULL);
	args_list = arr_to_dblst((void **)(argv + 2));
	args = dblst_to_arr(args_list);
	dblst_clear(&args_list, free);
	d->last_exit = exec(d, script, args, 0);
	safe_free(script);
	custom_exit(d, NULL, NULL, EXIT_CHILD);
	return (FCT_FAIL);
}

static void	init_msh(t_data *d, char *path, char **env)
{
	setup_signal(0, 0);
	init_data(d, path, env);
	d->prv_input = get_last_line(d, d->history_wd);
	if (d->prv_input)
		d->prv_input[ft_strlen(d->prv_input) - 1] = '\0';
}

int	main(int argc, char *argv[], char **env)
{
	t_data	data;
	int		started;

	started = 1;
	data.debug_mode = argc > 1;
	init_msh(&data, argv[0], env);
	if (argc > 1)
		return (handle_args(&data, argv));
	while (42)
	{
		if (!process_input(&data, started))
			break ;
		started = 0;
	}
	custom_exit(&data, NULL, NULL, EXIT_SUCCESS);
	return (0);
}
