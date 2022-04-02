/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paboutel <paboutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:30:17 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/02 18:56:28 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"
#include <math.h>

void	init_put_texture(t_wall wall, t_texture *texture,
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

void	put_floor(t_global_info *info, int x, int end)
{
	while (info->column_info[x].start < end)
	{
		cpy_data_pixel(&info->frame->data.data[info->column_info[x].start
			* info->frame->data.line_lenght + x * 4], info->conf->floor_rgb,
			(1 == info->frame->data.endian));
		info->column_info[x].start++;
	}
}

void	put_ceilling(t_global_info *info, int x, int start)
{
	while (start < info->column_info[x].end)
	{
		cpy_data_pixel(&info->frame->data.data[start
			* info->frame->data.line_lenght + x * 4], info->conf->ceilling_rgb,
			(1 == info->frame->data.endian));
		start++;
	}
}
