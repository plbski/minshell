/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:53:15 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/06 18:47:51 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "time.h"
#include "fcntl.h"
#include <termios.h>
#include "string.h"

#define PROMPT_SQARE 	"\u2589"
#define RED 			"\033[31m"
#define GREEN 			"\033[32m"
#define YELLOW 			"\033[33m"
#define BLUE 			"\033[34m"
#define MAGENTA			"\033[35m"
#define CYAN 			"\033[36m"
#define RESET 			"\033[0m"
#define GREY 			"\033[38;5;240m"
#define LIGHT_GREY 		"\033[38;5;250m"

#define MAX_MOBS		40

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define BONUSES_LEN	16
#define BONUSES			"dcsmlhwbDCSMLHWB"

#define BONUS_SPEED		'd'
#define BONUS_SCORE		'c'
#define BONUS_ATKSPD 	's'
#define BONUS_MULT		'm'
#define BONUS_SHIELD	'l'
#define BONUS_LIFE		'h'
#define BONUS_POW		'w'
#define BONUS_BOMB		'b'

#define LASER_PRJ		':'
#define LASER_LEFTOVER	';'

#define GRID_X 			11
#define PLR_SIZE 		7
#define MAX_PLR_PRJ		900

typedef struct s_vec2
{
	int	x;
	int	y;
}	t_vec2;

typedef enum e_dir
{
	up,
	down,
	left,
	right,
	left_up,
	right_up,
	left_down,
	right_down,
	dir_count,
}	t_dir;

typedef enum e_prj_type
{
	base,
	follow,
	bomb,
	laser,
	matrix,
	big,
	prj_type_count,
}	t_prj_type;

typedef struct s_proj
{
	int				active;
	int				time;
	int				time_left;
	int				index;
	int				speed;
	t_prj_type		type;
	t_dir			dir;
	struct s_proj	*prv;
	struct s_proj	*next;
}	t_proj;

typedef struct s_player
{
	t_vec2		pos;
	t_vec2		mv;
	int			trg_x;
	t_proj		*proj;
	t_prj_type	prj_type;
	int			prj_type_count;
	int			speed;
	int			index;
	int			shield;
	int			atk_spd;
	int			mult;
	int			pow;
	int			life;
	int			bomb;
}	t_player;

typedef struct s_game
{
	t_player	plr;
	t_vec2		size;
	char		*str;
	int			len;
	int			time;
	int			score;
	int			game_over;
}	t_data;

//		update_game.c
void	update_str(t_data *d, int *o_count, int *mob_count, int *star_count);

//		update_proj.c
int		update_mob_prj(t_data *d, int i);
void	update_plr_prj(t_data *d, t_player *plr);

//		update.c
void	refill_entities(int o_count, int star_count, int mob_count, t_data *d);
int		handle_loop(t_data *d, int *input_return, int max_score);
void	matrix_loop(t_data *d, char **env);

//		render.c
void	render_matrix(t_data *d, int max_score);

//		input.c
void	update_plr(t_data *d, t_player *plr);
int		handle_input(t_data *d);

//		matrix_utils.c
int		r_range(int min, int max);
int		ft_atoi(const char *str);
void	set_nonblocking_input(int enable);
t_vec2	get_v2(int x, int y);
int		cmp_v2(t_vec2 a, t_vec2 b);
int		char_cmp(char *str, char c);

//		init.c
void	handle_end(int input_return, int score, int max_score, char **env);
int		load_max_score(void);
char	*init_matrix(t_data d, int *len);
int		main(int argc, char *argv[], char **env);
void	init_bonus(t_data *d, int index);

//		proj.c
void	launch_plr_proj(t_data *d, t_player *plr);
void	remove_proj(t_player *plr, t_proj *prj, t_data *d);
t_proj	*prj_head(t_proj *prj);
t_proj	*prj_tail(t_proj *prj);
t_proj	*init_proj(t_proj *prv, int index, t_dir dir, t_prj_type type);