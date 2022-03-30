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

void	put_texture_wall(t_wall wall, int column_height, int x, int draw_start, int draw_end, t_texture *texture, t_img *frame, t_put_texture *put_texture)
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
		put_texture->ptr_pix_texture = &put_texture->ptr_texture->data.data[(int)(fmod(wall.colision.y, 1) * put_texture->ptr_texture->width) *4];
	else if (wall.orientation == 'N' || wall.orientation == 'S')
		put_texture->ptr_pix_texture = &put_texture->ptr_texture->data.data[(int)(fmod(wall.colision.x, 1) * put_texture->ptr_texture->width) *4];
	put_texture->y_step = ((double)1 / (double)column_height) * put_texture->ptr_texture->height;
	if (draw_start < 0)
	{
		put_texture->y_pix = -draw_start * put_texture->y_step;
		draw_start = 0;
	}
	put_texture->ptr_pix_frame = &frame->data.data[(draw_start * frame->data.line_lenght) + (x * 4)];
	while (draw_start < draw_end)
	{
		cpy_data_pixel(put_texture->ptr_pix_frame, &put_texture->ptr_pix_texture[(int)put_texture->y_pix * put_texture->ptr_texture->data.line_lenght], put_texture->is_same_endian);
		draw_start++;
		put_texture->y_pix += put_texture->y_step;
		put_texture->ptr_pix_frame += frame->data.line_lenght;
	}
}

void	put_floor_ceilling(int start, int end, int x, char *rgb, t_data data)
{
	while (start < end)
	{
		cpy_data_pixel(&data.data[start * data.line_lenght + x * 4],
			rgb, (1 == data.endian));
		start++;
	}
}

void	print_column(t_wall wall, int x, t_global_info *info)
{
	int	i;
	int	column_height;
	int	draw_start;
	int	draw_end;

	i = 0;
	column_height = (int)((double)SCREEN_HEIGHT / wall.distance);
	draw_start = (-column_height / 2) + (SCREEN_HEIGHT / 2);
	draw_end = (column_height / 2) + (SCREEN_HEIGHT / 2);
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	put_floor_ceilling(info->column_info[x].start, draw_start, x,
			info->conf->floor_rgb, info->frame->data);
	put_floor_ceilling(draw_end, info->column_info[x].end, x,
		info->conf->ceilling_rgb, info->frame->data);
	put_texture_wall(wall, column_height, x, draw_start, draw_end,
		info->texture, info->frame, info->put_texture);
	if (draw_start < 0)
		draw_start = 0;
	info->column_info->start = draw_start;
	info->column_info->end = draw_end;
}
