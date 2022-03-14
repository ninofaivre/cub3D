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
#define SCREEN_HEIGHT 800
#include <header.h>
#include <calculation.h>

#include <stdio.h>
#include <mlx.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>

typedef	struct s_key_hook
{
	void		*mlx;
	void		*win;
	t_player	*player;
	t_map		*map;
}	t_key_hook;

static int	rgb_to_put_pixel(t_rgb *rgb)
{
	return ((rgb->b * pow(256, 0)) + (rgb->g * pow(256, 1)) + (rgb->r * pow(256, 2)));
}

static void	print_column(double	wall_distance, void *mlx, void *win, int x, t_rgb *floor_rgb, t_rgb *ceilling_rgb, t_column_info *column_info, bool care_about_last_frame, char wall_orientation)
{
	int	i;
	int	column_height;
	int draw_start;
	int	draw_end;

	i = 0;
	column_height = (int)((double)SCREEN_HEIGHT / wall_distance);
	draw_start = (-column_height / 2) + (SCREEN_HEIGHT / 2);
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (column_height / 2) + (SCREEN_HEIGHT / 2);
	if (draw_end > SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	while (i < SCREEN_HEIGHT)
	{
		if (i < draw_start && (i >= column_info->start || !care_about_last_frame))
			mlx_pixel_put(mlx, win, x, i, rgb_to_put_pixel(floor_rgb));
		else if (i > draw_end && (i <= column_info->end || !care_about_last_frame))
			mlx_pixel_put(mlx, win, x, i, rgb_to_put_pixel(ceilling_rgb));
		else if (i >= draw_start && i <= draw_end)
		{
			if (wall_orientation == 'N')
				mlx_pixel_put(mlx, win, x, i, 0x00FF0000);
			else if (wall_orientation == 'S')
				mlx_pixel_put(mlx, win, x, i, 0x00000000);
			else if (wall_orientation == 'E')
				mlx_pixel_put(mlx, win, x, i, 0x00FFFFFF);
			else if (wall_orientation == 'O')
				mlx_pixel_put(mlx, win, x, i, 0x00FFFF00);
		}
		i++;
	}
	column_info->start = draw_start;
	column_info->end = draw_end;
}

static t_column_info	*display_first_frame(t_global_info *info)
{
	t_wall			wall;
	double			angle;
	int				n_column;
	t_column_info	*column_info;

	n_column = 0;
	column_info = malloc(sizeof(t_column_info) * SCREEN_WIDTH);
	if (!column_info)
		return (NULL);
	while (n_column < SCREEN_WIDTH)
	{
		angle = ((double)(info->player.orientation + ((double)FOV / (double)2)) - (double)((double)n_column * ((double)FOV / (double)SCREEN_WIDTH)));
		if (angle < (double)0)
			angle = (double)360 + angle;
		else if (angle > (double)359)
			angle = angle - (double)359;
		wall = get_wall_distance(info->player.position, angle, info->map->content);
		print_column(wall.distance * cos(degrees_to_radians(angle - info->player.orientation)), info->mlx, info->win, n_column, info->conf->floor_rgb, info->conf->ceilling_rgb, &column_info[n_column], false, wall.orientation);
		n_column++;
	}
	return (column_info);
}

static int	display_one_frame(void *param)
{
	t_global_info *info;
	struct timeval time_before_frame;
	struct timeval time_after_frame;
	gettimeofday(&time_before_frame, NULL);

	t_wall	wall;
	double	angle;
	int		n_collumn;

	n_collumn = 0;
	info = param;
	if (update_player(&(info->player), keycode, info->map))
		printf("orientation : %f\n", info->player.orientation);
	while (n_collumn < SCREEN_WIDTH)
	{
		angle = ((double)(info->player.orientation + ((double)FOV / (double)2)) - (double)((double)n_collumn * ((double)FOV / (double)SCREEN_WIDTH)));
		if (angle < (double)0)
			angle = (double)360 + angle;
		else if (angle > (double)359)
			angle  = angle - (double)359;
		wall = get_wall_distance(info->player.position, angle, info->map->content);
		print_column(wall.distance * cos(degrees_to_radians(angle - info->player.orientation)), info->mlx, info->win, n_collumn, info->conf->floor_rgb, info->conf->ceilling_rgb, &info->column_info[n_collumn], true, wall.orientation);
		n_collumn++;
	}
	gettimeofday(&time_after_frame, NULL);
	printf("temps de rendu d'une frame : %ld ms, fps : %ld\n", (time_after_frame.tv_usec - time_before_frame.tv_usec) / 1000, 1000000 / (time_after_frame.tv_usec - time_before_frame.tv_usec));
	return (0);
}

static void	key_hook(int keycode, bool *key)
{
	if (keycode == 'z')
		key[z] = (key[z] == false) * true;
	else if (keycode == 'q')
		key[q] = (key[q] == false) * true;
	else if (keycode == 's')
		key[s] = (key[s] == false) * true;
	else if (keycode == 'd')
		key[d] = (key[d] == false) * true;
	else if (keycode == KEY_LEFT_ARROW)
		key[l] = (key[l] == false) * true;
	else if (keycode == KEY_RIGHT_ARROW)
		key[r] = (key[r] == false) * true;
}

void	init_info(t_global_info *info)
{

	info->mlx = mlx_init();
	info->win = mlx_new_window(info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D");
	info->key[z] = false;
	info->key[q] = false;
	info->key[s] = false;
	info->key[d] = false;
	info->key[l] = false;
	info->key[r] = false;
}

void	display(t_global_info *info)
{
	bool	keye[6];

	info->key = &keye;
	init_info(info);
	mlx_hook(info->win, 02, 1L, key_hook, info->key);
	mlx_hook(info->win, 03, 1L, key_hook, info->key);
	mlx_hook(info->win, 17, 1L << 17, mlx_loop_end, (void *)info->mlx);
	info->column_info = display_first_frame(info);
	if (!info->column_info)
		printf("first frame error !\n");
	mlx_loop_hook(info->mlx, display_one_frame, info);
	mlx_loop(info->mlx);
}
