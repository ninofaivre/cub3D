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
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 400
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

static int get_pixel(t_img img, int x, int y)
{
	//printf("data.bpp : %i | data.line_lenght : %i\n", img.data.bpp, img.data.line_lenght);

	img.data.data += ((y * img.data.line_lenght) + ((x * img.data.bpp) / 8));
	//int *test = (int *)img.data.data;
	//printf("test[0] : %i\n", test[0] >> (img.data.bpp / 4) * 0 & 0xFF);
	int	b = img.data.data[0];
	int g = img.data.data[1];
	int	r = img.data.data[2];
	//int	a = (*img.data.data >> ((img.data.bpp / 4) * 4));
	return ((b * pow(256, 0)) + (g * pow(256, 1)) + (r * pow(256, 2)));
}

static void	put_texture_wall(t_wall wall, int column_height, int x, int i, int draw_start, void *mlx, void *win, t_img north_texture)
{
	double	x_pix;
	double	y_pix;

	if (wall.orientation == 'N' || wall.orientation == 'S')
	{
		x_pix = fmod(wall.colision.x, 1) * north_texture.width;
		x_pix -= fmod(x_pix, 1);
	}
	else if (wall.orientation == 'E'|| wall.orientation == 'O')
	{
		x_pix = fmod(wall.colision.y, 1) * north_texture.width;
		x_pix -= fmod(x_pix, 1);
	}
	y_pix = ((double)(i - draw_start) / (double)column_height) * (double)north_texture.height;
	if (wall.orientation == 'N')
		mlx_pixel_put(mlx, win, x, i, get_pixel(north_texture, (int)x_pix, (int)y_pix));
	else
		mlx_pixel_put(mlx, win, x, i, 0x00FF0000);
}

static void	print_column(t_wall wall, void *mlx, void *win, int x, t_rgb *floor_rgb, t_rgb *ceilling_rgb, t_column_info *column_info, bool care_about_last_frame, t_img north_texture)
{
	int	i;
	int	column_height;
	int draw_start;
	int	draw_end;

	i = 0;
	column_height = (int)((double)SCREEN_HEIGHT / wall.distance);
	draw_start = (-column_height / 2) + (SCREEN_HEIGHT / 2);
	draw_end = (column_height / 2) + (SCREEN_HEIGHT / 2);
	while (i < SCREEN_HEIGHT)
	{
		if (i < draw_start && (i >= column_info->start || !care_about_last_frame))
			mlx_pixel_put(mlx, win, x, i, rgb_to_put_pixel(floor_rgb));
		else if (i >= draw_end && (i < column_info->end || !care_about_last_frame))
			mlx_pixel_put(mlx, win, x, i, rgb_to_put_pixel(ceilling_rgb));
		else if (i >= draw_start && i < draw_end)
			put_texture_wall(wall, column_height, x, i, draw_start, mlx, win, north_texture);
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
		wall.distance *= cos(degrees_to_radians(angle - info->player.orientation));
		print_column(wall, info->mlx, info->win, n_column, info->conf->floor_rgb, info->conf->ceilling_rgb, &column_info[n_column], false, info->texture->north);
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
	if (!(update_player(&(info->player), info->key, info->map)))
		return (0);
	//printf("orientation : %f\n", info->player.orientation);
	while (n_collumn < SCREEN_WIDTH)
	{
		angle = ((double)(info->player.orientation + ((double)FOV / (double)2)) - (double)((double)n_collumn * ((double)FOV / (double)SCREEN_WIDTH)));
		if (angle < (double)0)
			angle = (double)360 + angle;
		else if (angle > (double)359)
			angle  = angle - (double)359;
		wall = get_wall_distance(info->player.position, angle, info->map->content);
		wall.distance *= cos(degrees_to_radians(info->player.orientation - angle));
		print_column(wall, info->mlx, info->win, n_collumn, info->conf->floor_rgb, info->conf->ceilling_rgb, &info->column_info[n_collumn], true, info->texture->north);
		n_collumn++;
	}
	gettimeofday(&time_after_frame, NULL);
	//printf("temps de rendu d'une frame : %ld ms, fps : %ld\n", (time_after_frame.tv_usec - time_before_frame.tv_usec) / 1000, 1000000 / (time_after_frame.tv_usec - time_before_frame.tv_usec));
	return (0);
}

static void	key_hook(int keycode, t_key *key)
{
	printf("une touche a été pressée ou relâchée\n");
	if (keycode == 'z')
		key->z = (key->z == false) * true;
	else if (keycode == 'q')
		key->q = (key->q == false) * true;
	else if (keycode == 's')
		key->s = (key->s == false) * true;
	else if (keycode == 'd')
		key->d = (key->d == false) * true;
	else if (keycode == KEY_LEFT_ARROW)
		key->l_arrow = (key->l_arrow == false) * true;
	else if (keycode == KEY_RIGHT_ARROW)
		key->r_arrow = (key->r_arrow == false) * true;
}

void	init_info(t_global_info *info)
{
	info->mlx = mlx_init();
	info->win = mlx_new_window(info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D");
	mlx_do_key_autorepeatoff(info->mlx);
	info->key->z = false;
	info->key->q = false;
	info->key->s = false;
	info->key->d = false;
	info->key->l_arrow = false;
	info->key->r_arrow = false;
}

void	init_north(t_texture *texture, t_global_info *info)
{

	texture->north.img = mlx_xpm_file_to_image(info->mlx, info->conf->texture_path[north], &info->texture->north.width, &info->texture->north.height);
	texture->north.data.data = mlx_get_data_addr(texture->north.img, &texture->north.data.bpp, &texture->north.data.line_lenght, &texture->north.data.endian);
}

void	display(t_global_info *info)
{
	t_texture	texture;
	t_key		key;

	info->key = &key;
	info->texture = &texture;
	init_info(info);
	init_north(info->texture, info);
	mlx_hook(info->win, 02, 1L, key_hook, info->key);
	mlx_hook(info->win, 03, 1L<<1, key_hook, info->key);
	mlx_hook(info->win, 17, 1L << 17, mlx_loop_end, (void *)info->mlx);
	info->column_info = display_first_frame(info);
	if (!info->column_info)
		printf("first frame error !\n");
	mlx_loop_hook(info->mlx, display_one_frame, info);
	mlx_loop(info->mlx);
}
