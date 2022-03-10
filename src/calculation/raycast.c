/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:30:17 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/10 21:38:08 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FOV 60
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
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

static void	print_floor_ceiling(t_rgb *floor_rgb, t_rgb *ceilling_rgb)
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
				mlx_pixel_put(mlx, win, x, y, rgb_to_put_pixel(rgb_floor));
			x++;
		}
		y++;
	}
}

static void	display_one_frame(void *mlx, void *win, t_player player, char **map)
{
	double	angle;
	double	beta;
	double	cos_beta;
	int	n_collumn;

	n_collumn = 0;
	print_floor_ceiling(conf->floor_rgb, conf->ceilling_rgb);
	while (n_collumn < SCREEN_WIDTH)
	{
		angle = ((double)(player.orientation + ((double)FOV / (double)2)) - (double)((double)n_collumn * ((double)FOV / (double)SCREEN_WIDTH)));
		if (angle < (double)0)
			angle = (double)360 + angle;
		else if (angle > (double)359)
			angle  = angle - (double)359;
		beta = (double)angle - (double)player.orientation;
		cos_beta = (double)cos(beta * (M_PI / (double)180));
		print_column((get_wall_distance(player.position, angle, map) * cos_beta), mlx, win, n_collumn);
		n_collumn++;
	}
}

static void	key_hook(int keycode, t_key_hook *key)
{
	if (update_player(key->player, keycode, key->map))
	{
		printf("orientation : %f\n", key->player->orientation);
		printf("orientation wall_distance : %f\n", get_wall_distance(key->player->position, key->player->orientation, key->map->content));
		display_one_frame(key->mlx, key->win, *(key->player), key->map->content);
	}
}

void	display(t_global_info *info)
{
	info->mlx = mlx_init();
	info->win = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "lkqsdflkskldfqk");
	
	mlx_hook(info->win, 02, 1L, key_hook, info);
	display_one_frame(mlx, win, *player, map->content);
	mlx_do_key_autorepeaton(mlx);
	mlx_loop(mlx);
}