/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paboutel <paboutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:30:17 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/05 21:15:56 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"
#include "mlx.h"
#include <stdlib.h>

static bool	load_image(char *texture_path, t_img *img, void *mlx)
{
	img->img = mlx_xpm_file_to_image(mlx, texture_path, &img->width,
			&img->height);
	if (!img->img)
	{
		print_error("Mlx function xpm_file_to_image failed to load an asset\n");
		return (true);
	}
	img->data.data = mlx_get_data_addr(img->img, &img->data.bpp,
			&img->data.line_lenght, &img->data.endian);
	if (!img->data.data)
	{
		mlx_destroy_image(mlx, img->img);
		print_error("Mlx function get_data_addr failed to load an asset\n");
		return (true);
	}
	if (img->data.bpp != 32)
	{
		print_error("Bit Per Pixel from one of the assets is different than 32,\
				please try again with a bpp of 32 !\n");
		mlx_destroy_image(mlx, img->img);
		return (true);
	}
	return (false);
}

static void	set_info_and_texture_ptr_null(t_global_info *info)
{
	info->mlx = NULL;
	info->win = NULL;
	info->frame->img = NULL;
	info->frame->data.data = NULL;
	info->column_info = NULL;
	info->texture->north.img = NULL;
	info->texture->north.data.data = NULL;
	info->texture->west.img = NULL;
	info->texture->west.data.data = NULL;
	info->texture->east.img = NULL;
	info->texture->east.data.data = NULL;
	info->texture->south.img = NULL;
	info->texture->south.data.data = NULL;
	info->key->mlx = NULL;
}

bool	init_raycast_info(t_global_info *info)
{
	set_info_and_texture_ptr_null(info);
	info->mlx = mlx_init();
	if (!info->mlx)
		return (true);
	info->win = mlx_new_window(info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D");
	info->frame->img = mlx_new_image(info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!info->win || !info->frame->img)
		return (true);
	info->frame->data.data = mlx_get_data_addr(info->frame->img,
			&info->frame->data.bpp, &info->frame->data.line_lenght,
			&info->frame->data.endian);
	if (!info->frame->data.data)
		return (true);
	info->first_frame = true;
	info->key->z = false;
	info->key->q = false;
	info->key->s = false;
	info->key->d = false;
	info->key->l_arrow = false;
	info->key->r_arrow = false;
	info->key->mlx = info->mlx;
	return (false);
}

bool	init_texture(t_texture *texture, t_global_info *info)
{
	if (load_image(info->conf->texture_path[north], &texture->north, info->mlx))
		return (true);
	if (load_image(info->conf->texture_path[west], &texture->west, info->mlx))
		return (true);
	if (load_image(info->conf->texture_path[east], &texture->east, info->mlx))
		return (true);
	if (load_image(info->conf->texture_path[south], &texture->south, info->mlx))
		return (true);
	return (false);
}

t_column_info	*init_column_info(void)
{
	int				i;
	t_column_info	*column_info;

	i = 0;
	column_info = malloc(sizeof(t_column_info) * SCREEN_WIDTH);
	if (!column_info)
	{
		print_error("Malloc failed in function init_column_info\n");
		return (NULL);
	}
	while (i < SCREEN_WIDTH)
	{
		column_info[i].start = 0;
		column_info[i].end = SCREEN_HEIGHT - 1;
		i++;
	}
	return (column_info);
}
