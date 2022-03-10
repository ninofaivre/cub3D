/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:30:17 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/10 22:47:45 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FOV 60
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#include <header.h>
#include <calculation.h>

#include <stdio.h>
#include <mlx.h>
#include <math.h>

typedef	struct s_key_hook
{
	void		*mlx;
	void		*win;
	t_player	*player;
	t_map		*map;
}	t_key_hook;

static void	print_column(double	wall_distance, void *mlx, void *win, int x)
{
	int	column_height;
	int draw_start;
	int	draw_end;

	column_height = (int)((double)SCREEN_HEIGHT / wall_distance);
	draw_start = (-column_height / 2) + (SCREEN_HEIGHT / 2);
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (column_height / 2) + (SCREEN_HEIGHT / 2);
	if (draw_end > SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	while (draw_start < draw_end)
	{
		mlx_pixel_put(mlx, win, x, draw_start, 0x00FF0000);
		draw_start++;
	}
}

static int	rgb_to_put_pixel(t_rgb *rgb)
{
	return ((rgb->b * pow(256, 0)) + (rgb->g * pow(256, 1)) + (rgb->r * pow(256, 2)));
}

static void	print_floor_ceiling(t_rgb *floor_rgb, t_rgb *ceilling_rgb, void *mlx, void *win)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			if (y > SCREEN_HEIGHT / 2)
				mlx_pixel_put(mlx, win, x, y, rgb_to_put_pixel(ceilling_rgb));
			else
				mlx_pixel_put(mlx, win, x, y, rgb_to_put_pixel(floor_rgb));
			x++;
		}
		y++;
	}
}

static void	display_one_frame(t_global_info *info)
{
	double	angle;
	double	beta;
	double	cos_beta;
	int	n_collumn;

	n_collumn = 0;
	print_floor_ceiling(info->conf->floor_rgb, info->conf->ceilling_rgb, info->mlx, info->win);
	while (n_collumn < SCREEN_WIDTH)
	{
		angle = ((double)(info->player.orientation + ((double)FOV / (double)2)) - (double)((double)n_collumn * ((double)FOV / (double)SCREEN_WIDTH)));
		if (angle < (double)0)
			angle = (double)360 + angle;
		else if (angle > (double)359)
			angle  = angle - (double)359;
		beta = (double)angle - (double)info->player.orientation;
		cos_beta = (double)cos(beta * (M_PI / (double)180));
		print_column((get_wall_distance(info->player.position, angle, info->map->content) * cos_beta), info->mlx, info->win, n_collumn);
		n_collumn++;
	}
}

static void	key_hook(int keycode, t_global_info *info)
{
	if (update_player(&(info->player), keycode, info->map))
	{
		printf("orientation : %f\n", info->player.orientation);
		printf("orientation wall_distance : %f\n", get_wall_distance(info->player.position, info->player.orientation, info->map->content));
		display_one_frame(info);
	}
}

void	display(t_global_info *info)
{
	info->mlx = mlx_init();
	info->win = mlx_new_window(info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "lkqsdflkskldfqk");
	
	mlx_hook(info->win, 02, 1L, key_hook, info);
	display_one_frame(info);
	mlx_do_key_autorepeaton(info->mlx);
	mlx_loop(info->mlx);
}