/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paboutel <paboutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:30:17 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/30 16:24:24 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.h>
#include <calculation.h>
#include <stdio.h>
#include <mlx.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#define FOV 60
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

static int	display_one_frame(void *param)
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

void	display(t_global_info *info)
{
	t_put_texture	put_texture;
	t_texture		texture;
	t_img			frame;
	t_key			key;

	info->key = &key;
	info->texture = &texture;
	info->frame = &frame;
	info->put_texture = &put_texture;
	init_raycast_info(info);
	init_texture(&texture, info);
	mlx_hook(info->win, 02, 1L, key_hook_press, info->key);
	mlx_hook(info->win, 03, 1L << 1, key_hook_release, info->key);
	mlx_hook(info->win, 17, 1L << 17, mlx_loop_end, (void *)info->mlx);
	info->column_info = init_column_info();
	if (!info->column_info)
		printf("first frame error !\n");
	mlx_loop_hook(info->mlx, display_one_frame, info);
	mlx_loop(info->mlx);
}
