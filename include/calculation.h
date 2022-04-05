/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paboutel <paboutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:42:44 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/05 21:14:51 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALCULATION_H
# define CALCULATION_H

# include "parsing.h"

# define ORIENT_STEP 2.1
# define MOOVE_STEP 0.09
# define FOV 60
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 800

typedef struct s_column_info
{
	int	start;
	int	end;
}	t_column_info;

typedef struct s_data
{
	int		bpp;
	int		line_lenght;
	int		endian;
	char	*data;
}	t_data;

typedef struct s_img
{
	void	*img;
	t_data	data;
	int		width;
	int		height;
}	t_img;

typedef struct s_texture
{
	t_img	north;
	t_img	west;
	t_img	south;
	t_img	east;
}	t_texture;

typedef struct s_wall
{
	char		orientation;
	double		distance;
	t_position	colision;
}	t_wall;

typedef struct s_put_texture
{
	t_img	*ptr_texture;
	double	y_pix;
	double	y_step;
	bool	is_same_endian;
	char	*ptr_pix_frame;
	char	*ptr_pix_texture;
	int		x;
	int		column_height;
}	t_put_texture;

typedef struct s_side_lenght
{
	double	x_adja;
	double	y_adja;
	double	x_oppo;
	double	y_oppo;
}	t_side_lenght;

double			degrees_to_radians(double degrees);
double			calc_distance(t_position position_1, t_position position_2);

void			get_next_intersection(t_position *position, double angle);

bool			is_in_a_wall(double x, double y, t_map *map);

void			init_put_texture(t_wall wall, t_texture *texture,
					t_img *frame, t_put_texture *put_texture);
void			put_texture_wall(int draw_start, int draw_end,
					t_img *frame, t_put_texture *put_texture);
void			put_floor(t_global_info *info, int x, int end);
void			put_ceilling(t_global_info *info, int x, int start);

int				display_one_frame(void *param);

bool			init_raycast_info(t_global_info *info);
bool			init_texture(t_texture *texture, t_global_info *info);
t_column_info	*init_column_info(void);

void			cpy_data_pixel(char *ptr_pix_data1, char *ptr_pix_data2,
					bool same_endian);
double			calculate_angle(int orientation, int n_collumn);

bool			update_player(t_player *player, t_key *key, t_map *map);

char			does_position_touch_a_wall(t_position position, char **map);

t_wall			get_wall_distance(t_position player_position,
					double angle, char **map);

void			raycast_clean(t_global_info *info, bool error);

#endif
