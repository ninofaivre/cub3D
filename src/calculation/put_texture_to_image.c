/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_texture_to_image.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paboutel <paboutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:30:17 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/30 15:12:21 by nfaivre          ###   ########.fr       */
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

static void	init_put_texture(t_wall wall, t_texture *texture,
t_img *frame, t_put_texture *put_texture)
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
	put_texture->is_same_endian = (frame->data.endian
			== put_texture->ptr_texture->data.endian);
	if (wall.orientation == 'O' || wall.orientation == 'E')
		put_texture->ptr_pix_texture = &put_texture->ptr_texture->data.data[
			(int)(fmod(wall.colision.y, 1)
				* put_texture->ptr_texture->width) *4];
	else if (wall.orientation == 'N' || wall.orientation == 'S')
		put_texture->ptr_pix_texture = &put_texture->ptr_texture->data.data[
			(int)(fmod(wall.colision.x, 1)
				* put_texture->ptr_texture->width) *4];
	put_texture->y_step = ((double)1 / (double)put_texture->column_height)
		* put_texture->ptr_texture->height;
}

void	put_texture_wall(int draw_start, int draw_end,
t_img *frame, t_put_texture *put_texture)
{
	if (draw_start < 0)
	{
		put_texture->y_pix = -draw_start * put_texture->y_step;
		draw_start = 0;
	}
	put_texture->ptr_pix_frame = &frame->data.data[
		(draw_start * frame->data.line_lenght) + (put_texture->x * 4)];
	while (draw_start < draw_end)
	{
		cpy_data_pixel(put_texture->ptr_pix_frame,
			&put_texture->ptr_pix_texture[(int)put_texture->y_pix
			* put_texture->ptr_texture->data.line_lenght],
			put_texture->is_same_endian);
		draw_start++;
		put_texture->y_pix += put_texture->y_step;
		put_texture->ptr_pix_frame += frame->data.line_lenght;
	}
}

static void	put_floor(t_global_info *info, int x, int end)
{
	while (info->column_info[x].start < end)
	{
		cpy_data_pixel(&info->frame->data.data[info->column_info[x].start
			* info->frame->data.line_lenght + x * 4], info->conf->floor_rgb,
			(1 == info->frame->data.endian));
		info->column_info[x].start++;
	}
}

static void	put_ceilling(t_global_info *info, int x, int start)
{
	while (start < info->column_info[x].end)
	{
		cpy_data_pixel(&info->frame->data.data[start
			* info->frame->data.line_lenght + x * 4], info->conf->ceilling_rgb,
			(1 == info->frame->data.endian));
		start++;
	}
}

void	print_column(t_wall wall, int x, t_global_info *info)
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
