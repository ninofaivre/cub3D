/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paboutel <paboutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:30:17 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/28 12:05:36 by paboutel         ###   ########.fr       */
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
#include <unistd.h>

static void	cpy_data_pixel(char *ptr_pix_data1, char *ptr_pix_data2, bool same_endian)
{
	if (same_endian)
	{
		ptr_pix_data1[0] = ptr_pix_data2[0];
		ptr_pix_data1[1] = ptr_pix_data2[1];
		ptr_pix_data1[2] = ptr_pix_data2[2];
		ptr_pix_data1[3] = ptr_pix_data2[3];
	}
	else
	{
		ptr_pix_data1[0] = ptr_pix_data2[3];
		ptr_pix_data1[1] = ptr_pix_data2[2];
		ptr_pix_data1[2] = ptr_pix_data2[1];
		ptr_pix_data1[3] = ptr_pix_data2[0];
	}
}

static void	put_texture_wall(t_wall wall, int column_height, int x, int draw_start, int draw_end, t_texture *texture, t_img *frame, t_put_texture *put_texture)
{
	put_texture->y_pix = 0.0;
	if (wall.orientation == 'N')
		put_texture->ptr_texture = &texture->north;
	else if (wall.orientation == 'S')
		put_texture->ptr_texture = &texture->south;
	else if (wall.orientation == 'E')
		put_texture->ptr_texture = &texture->east;
	else if (wall.orientation == 'O')
		put_texture->ptr_texture = &texture->west;
	put_texture->is_same_endian = (frame->data.endian == put_texture->ptr_texture->data.endian);
	if (wall.orientation == 'O' || wall.orientation == 'E')
		put_texture->ptr_pix_texture = &put_texture->ptr_texture->data.data[(int)(fmod(wall.colision.y, 1) * put_texture->ptr_texture->width) * 4];
	else if (wall.orientation == 'N' || wall.orientation == 'S')
		put_texture->ptr_pix_texture = &put_texture->ptr_texture->data.data[(int)(fmod(wall.colision.x, 1) * put_texture->ptr_texture->width) * 4];
	put_texture->y_step = ((double)1 / (double)column_height) * put_texture->ptr_texture->height;
	if (draw_start < 0)
	{
		put_texture->y_pix = -draw_start * put_texture->y_step;
		draw_start = 0;
	}
	put_texture->ptr_pix_frame = &frame->data.data[(draw_start * frame->data.line_lenght) + (x * 4)];
	while (draw_start < draw_end)
	{
		cpy_data_pixel(put_texture->ptr_pix_frame, &put_texture->ptr_pix_texture[(int)put_texture->y_pix * put_texture->ptr_texture->data.line_lenght], put_texture->is_same_endian); // this need to be tested deeper but cpy_data_pixel seems to be more effiscient in this case than a put_data_pixel (need to be tested on mac)
		draw_start++;
		put_texture->y_pix += put_texture->y_step;
		put_texture->ptr_pix_frame += frame->data.line_lenght;
	}
}

static void	put_floor_ceilling(int start, int end, int x, char *rgb, t_data data)
{
	while (start < end)
	{
		cpy_data_pixel(&data.data[start * data.line_lenght + x * 4], rgb, (1 == data.endian));
		start++;
	}
}

static void	print_column(t_wall wall, void *mlx, void *win, int x, char *floor_rgb, char *ceilling_rgb, t_column_info *column_info, bool care_about_last_frame, t_texture *texture, t_img *frame, t_put_texture *put_texture)
{
	int	i;
	int	column_height;
	int draw_start;
	int	draw_end;

	i = 0;
	column_height = (int)((double)SCREEN_HEIGHT / wall.distance);
	draw_start = (-column_height / 2) + (SCREEN_HEIGHT / 2);
	draw_end = (column_height / 2) + (SCREEN_HEIGHT / 2);
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	if (!care_about_last_frame)
	{
		put_floor_ceilling(0, draw_start, x, floor_rgb, frame->data);
		put_floor_ceilling(draw_end, SCREEN_HEIGHT - 1, x, ceilling_rgb, frame->data);
	}
	else
	{
		put_floor_ceilling(column_info->start, draw_start, x, floor_rgb, frame->data);
		put_floor_ceilling(draw_end, column_info->end, x, ceilling_rgb, frame->data);
	}
	put_texture_wall(wall, column_height, x, draw_start, draw_end, texture, frame, put_texture);
	if (draw_start < 0)
		draw_start = 0;
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
		print_column(wall, info->mlx, info->win, n_column, info->conf->floor_rgb, info->conf->ceilling_rgb, &column_info[n_column], false, info->texture, info->frame, info->put_texture);
		n_column++;
	}
	//mlx_sync(2, info->frame->img);
	mlx_put_image_to_window(info->mlx, info->win, info->frame->img, 0, 0);
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
		print_column(wall, info->mlx, info->win, n_collumn, info->conf->floor_rgb, info->conf->ceilling_rgb, &info->column_info[n_collumn], true, info->texture, info->frame, info->put_texture);
		n_collumn++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->frame->img, 0, 0);
	gettimeofday(&time_after_frame, NULL);
	printf("temps de rendu d'une frame : %ld ms, fps : %ld\n", (time_after_frame.tv_usec - time_before_frame.tv_usec) / 1000, 1000000 / (time_after_frame.tv_usec - time_before_frame.tv_usec));
	return (0);
}

static void	key_hook_press(int keycode, t_key *key)
{
	if (keycode == 'z')
		key->z = true;
	else if (keycode == 'q')
		key->q = true;
	else if (keycode == 's')
		key->s = true;
	else if (keycode == 'd')
		key->d = true;
	else if (keycode == KEY_LEFT_ARROW)
		key->l_arrow = true;
	else if (keycode == KEY_RIGHT_ARROW)
		key->r_arrow = true;
}

static void	key_hook_release(int keycode, t_key *key)
{
	if (keycode == 'z')
		key->z = false;
	else if (keycode == 'q')
		key->q = false;
	else if (keycode == 's')
		key->s = false;
	else if (keycode == 'd')
		key->d = false;
	else if (keycode == KEY_LEFT_ARROW)
		key->l_arrow = false;
	else if (keycode == KEY_RIGHT_ARROW)
		key->r_arrow = false;
}

void	display(t_global_info *info)
{
	t_put_texture	put_texture;
	t_texture	texture;
	t_img		frame;
	t_key		key;

	info->key = &key;
	info->texture = &texture;
	info->frame = &frame;
	info->put_texture = &put_texture;
	init_raycast_info(info);
	init_texture(&texture, info);
	mlx_hook(info->win, 02, 1L, key_hook_press, info->key);
	mlx_hook(info->win, 03, 1L<<1, key_hook_release, info->key);
	mlx_hook(info->win, 17, 1L << 17, mlx_loop_end, (void *)info->mlx);
	info->column_info = display_first_frame(info);
	if (!info->column_info)
		printf("first frame error !\n");
	mlx_loop_hook(info->mlx, display_one_frame, info);
	mlx_loop(info->mlx);
}
