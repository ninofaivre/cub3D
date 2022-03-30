/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init.c                                     :+:      :+:    :+:   */
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

void	init_raycast_info(t_global_info *info)
{
	info->mlx = mlx_init();
	info->win = mlx_new_window(info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D");
	info->frame->img = mlx_new_image(info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	info->frame->data.data = mlx_get_data_addr(info->frame->img,
			&info->frame->data.bpp, &info->frame->data.line_lenght,
			&info->frame->data.endian);
	info->first_frame = true;
	mlx_do_key_autorepeatoff(info->mlx);
	info->key->z = false;
	info->key->q = false;
	info->key->s = false;
	info->key->d = false;
	info->key->l_arrow = false;
	info->key->r_arrow = false;
}

void	init_texture(t_texture *texture, t_global_info *info)
{
	texture->north.img = mlx_xpm_file_to_image(info->mlx,
			info->conf->texture_path[north], &info->texture->north.width,
			&info->texture->north.height);
	texture->north.data.data = mlx_get_data_addr(texture->north.img,
			&texture->north.data.bpp, &texture->north.data.line_lenght,
			&texture->north.data.endian);
	texture->west.img = mlx_xpm_file_to_image(info->mlx,
			info->conf->texture_path[west], &info->texture->west.width,
			&info->texture->west.height);
	texture->west.data.data = mlx_get_data_addr(texture->west.img,
			&texture->west.data.bpp, &texture->west.data.line_lenght,
			&texture->west.data.endian);
	texture->east.img = mlx_xpm_file_to_image(info->mlx,
			info->conf->texture_path[east], &info->texture->east.width,
			&info->texture->east.height);
	texture->east.data.data = mlx_get_data_addr(texture->east.img,
			&texture->east.data.bpp, &texture->east.data.line_lenght,
			&texture->east.data.endian);
	texture->south.img = mlx_xpm_file_to_image(info->mlx,
			info->conf->texture_path[south], &info->texture->south.width,
			&info->texture->south.height);
	texture->south.data.data = mlx_get_data_addr(texture->south.img,
			&texture->south.data.bpp, &texture->south.data.line_lenght,
			&texture->south.data.endian);
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
