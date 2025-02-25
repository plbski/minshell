/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:58:30 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/25 11:43:59 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static void	split_prm(t_data *d, char **str, char *headcol, char *seg)
{
	const char	*cl[] = {D4, D3, D2, D1, D0};
	char		**spl;
	int			i;
	int			arr_len;

	spl = ms_split(d, *str, '/');
	arr_len = get_arr_len((void **)spl);
	if (seg && ft_atoi(seg) / arr_len < 1)
		setstr(d, &seg, ft_itoa(arr_len));
	i = arr_len;
	while (i-- > 1)
	{
		if (i == 1)
			setstr(d, &spl[i], ms_strjoin(d, "/", spl[i]));
		if (spl[i + 1] && seg && ft_strlen(spl[i]) > ft_atoi(seg) / arr_len)
			spl[i][ft_atoi(seg) / arr_len] = '\0';
		if (!spl[i + 1] || char_in_str('$', spl[i]))
			setstr(d, &spl[i], ms_strjoin(d, headcol, spl[i]));
		else
			setstr(d, &spl[i], ft_megajoin(cl[(i * 5) / arr_len], \
				spl[i], "/", DRESET));
	}
	setstr(d, str, contract_str(d, spl));
	free_void_array((void ***)&spl);
	safe_free(seg);
}

char	*get_prompt_message(t_data *d)
{
	char	*msh;
	char	*cut_cwd;
	char	*prmpt;

	msh = ft_megajoin("\001" PRM_START "\002", "msh ", DRESET, NULL);
	if (!msh)
		return (NULL);
	if (same_str(d->cwd, "/"))
		return (setstr(d, &msh, ms_strjoin(d, msh, "/$ ")), msh);
	cut_cwd = ms_strjoin(d, "", d->cwd);
	replace_strstr(d, &cut_cwd, d->home_wd, "~");
	prmpt = ms_strjoin(d, msh, cut_cwd);
	if (char_in_str('/', prmpt) && PRM_SEGLEN > 0)
		split_prm(d, &prmpt, PRM_HEAD, get_env_value(d, d->var_list, "SEGLEN"));
	if (!prmpt)
		custom_exit(d, "Prompt alloc failed", NULL, EXIT_FAILURE);
	setstr(d, &prmpt, \
			ft_megajoin(prmpt, "\001" PRM_CMB "\002", "$ ", DRESET));
	return (free(cut_cwd), free(msh), prmpt);
}

char	*custom_get_cwd(t_data *d)
{
	char	*working_dir_buff;

	working_dir_buff = malloc(999);
	if (!working_dir_buff)
		custom_exit(d, "alloc for cwd", NULL, EXIT_FAILURE);
	if (!getcwd(working_dir_buff, 999))
	{
		free(working_dir_buff);
		custom_exit(d, "alloc for cwd", NULL, EXIT_FAILURE);
	}
	return (working_dir_buff);
}

int	update_cwd(t_data *data)
{
	char	*working_dir_buff;

	working_dir_buff = custom_get_cwd(data);
	if (data->cwd)
	{
		if (data->prev_cwd)
			free(data->prev_cwd);
		data->prev_cwd = ms_strdup(data, data->cwd);
		free(data->cwd);
	}
	set_key_value(data, data->env_list, "OLDPWD", data->prev_cwd);
	set_key_value(data, data->env_list, "PWD", working_dir_buff);
	data->cwd = working_dir_buff;
	setstr(data, &data->prompt_msg, get_prompt_message(data));
	return (1);
}
