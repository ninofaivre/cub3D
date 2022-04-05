/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paboutel <paboutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:30:17 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/05 21:18:35 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"
#include "mlx.h"
#include <math.h>

static void	print_column(t_wall wall, int x, t_global_info *info)
{
	int	column_height;
	int	draw_start;
	int	draw_end;

	column_height = (int)((double)SCREEN_HEIGHT / wall.distance);
	draw_start = (-column_height / 2) + (SCREEN_HEIGHT / 2);
	draw_end = (column_height / 2) + (SCREEN_HEIGHT / 2);
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	put_floor(info, x, draw_start);
	put_ceilling(info, x, draw_end);
	info->put_texture->x = x;
	info->put_texture->column_height = column_height;
	init_put_texture(wall, info->texture, info-> frame, info->put_texture);
	put_texture_wall(draw_start, draw_end, info->frame, info->put_texture);
	if (draw_start < 0)
		draw_start = 0;
	info->column_info[x].start = draw_start;
	info->column_info[x].end = draw_end;
}

int	display_one_frame(void *param)
{
	t_global_info	*info;
	t_wall			wall;
	double			angle;
	int				n_collumn;

	n_collumn = 0;
	info = param;
	if (!(update_player(&(info->player), info->key,
				info->map)) && !info->first_frame)
		return (0);
	if (info->first_frame)
		info->first_frame = false;
	while (n_collumn < SCREEN_WIDTH)
	{
		angle = calculate_angle(info->player.orientation, n_collumn);
		wall = get_wall_distance(info->player.position,
				angle, info->map->content);
		wall.distance *= cos(degrees_to_radians
				(info->player.orientation - angle));
		print_column(wall, n_collumn, info);
		n_collumn++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->frame->img, 0, 0);
	return (0);
}
