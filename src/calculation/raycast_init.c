/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paboutel <paboutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:30:17 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/04 21:50:16 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"
#include <mlx.h>
#include <stdlib.h>

static bool	load_image(char *texture_path, t_img *img, void *mlx)
{
	img->img = mlx_xpm_file_to_image(mlx, texture_path, &img->width, &img->height);
	if (!img->img)
	{
		print_error("A malloc failed (xpm_file_to_image)");
		return (true);
	}
	img->data.data = mlx_get_data_addr(img->img, &img->data.bpp, &img->data.line_lenght, &img->data.endian);
	if (!img->data.data)
	{
		mlx_destroy_image(mlx, img->img);
		print_error("A malloc failed (get_data_addr)\n");
		return (true);
	}
	if (img->data.bpp != 32)
	{
		print_error("Bit Per Pixel from one of the assets is different than 32, please try again with a bpp of 32 !\n");
		free(img->data.data);
		mlx_destroy_image(mlx, img->img);
		return (true);
	}
	return (false);
}

bool	init_raycast_info(t_global_info *info)
{
	info->win = NULL;
	info->frame->img = NULL;
	info->frame->data.data = NULL;
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
	return (false);
}

bool	init_texture(t_texture *texture, t_global_info *info)
{
	texture->north.img = NULL;
	texture->north.data.data = NULL;	
	texture->west.img = NULL;
	texture->west.data.data = NULL;	
	texture->east.img = NULL;
	texture->east.data.data = NULL;	
	texture->south.img = NULL;
	texture->south.data.data = NULL;	
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
		return (NULL);
	while (i < SCREEN_WIDTH)
	{
		column_info[i].start = 0;
		column_info[i].end = SCREEN_HEIGHT - 1;
		i++;
	}
	return (column_info);
}
