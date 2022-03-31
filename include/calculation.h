/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paboutel <paboutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:42:44 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/28 20:34:06 by paboutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALCULATION_H
# define CALCULATION_H

# include "header.h"

# define KEY_RIGHT_ARROW 65363
# define KEY_LEFT_ARROW 65361
# define ORIENT_STEP 2.1
# define MOOVE_STEP 0.09

typedef struct s_column_info
{
	int	start;
	int	end;
}	t_column_info;

bool	update_player(t_player *player, t_key *key, t_map *map);
char	does_position_touch_a_wall(t_position position, char **map);

bool	is_in_a_wall(double x, double y, t_map *map);

void	init_texture(t_texture *texture, t_global_info *info);
void	init_raycast_info(t_global_info *info);
t_column_info	*init_column_info(void);

void	key_hook_press(int keycode, t_key *key);
void	key_hook_release(int keycode, t_key *key);

void	cpy_data_pixel(char *ptr_pix_data1, char *ptr_pix_data2, bool same_endian);
double	calculate_angle(int orientation, int n_collumn);

void	print_column(t_wall wall, int x, t_global_info *info);
void	put_floor_ceilling(int start, int end, int x, char *rgb, t_data data);

#endif
