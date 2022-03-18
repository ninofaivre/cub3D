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
#include <unistd.h>

typedef	struct s_key_hook
{
	void		*mlx;
	void		*win;
	t_player	*player;
	t_map		*map;
}	t_key_hook;

static int	rgb_to_put_pixel(t_rgb *rgb)
{
	return (rgb->r << 16 | rgb->g << 8 | rgb->b);
}

static int get_data_pixel(t_data data, int x, int y)
{
	unsigned char	*ptr_pix;

	if (x < 0 || y < 0)
		return (-1);
	ptr_pix = (unsigned char *)&data.data[(y * data.line_lenght) + ((x * data.bpp) / 8)];
	if (data.endian == 0)
		return (ptr_pix[3] << 24 | ptr_pix[2] << 16 | ptr_pix[1] << 8 | ptr_pix[0]);
	else if (data.endian == 1)
		return (ptr_pix[0] << 24 | ptr_pix[1] << 16 | ptr_pix[2] << 8 | ptr_pix[3]);
	return (-1);
}

static void	put_data_pixel(t_data data, int x, int y, int rgb)
{
	unsigned char	*ptr_pix;

	if (x < 0 || y < 0 || rgb < 0)
		return ;
	ptr_pix = (unsigned char *)&data.data[(y * data.line_lenght) + ((x * data.bpp) / 8)];
	if (get_data_pixel(data, x, y) == rgb)
		return ;
	if (data.endian == 0)
	{
		ptr_pix[0] = rgb;
		ptr_pix[1] = rgb >> 8;
		ptr_pix[2] = rgb >> 16;
		ptr_pix[3] = rgb >> 24;
	}
	else if (data.endian == 1)
	{
		ptr_pix[3] = rgb;
		ptr_pix[2] = rgb >> 8;
		ptr_pix[1] = rgb >> 16;
		ptr_pix[0] = rgb >> 24;
	}
}

static void	put_texture_wall(t_wall wall, int column_height, int x, int i, int draw_start, void *mlx, void *win, t_texture *texture, t_img *frame_old, t_img *frame_new)
{
	double	x_pix;
	double	y_pix;

	if (wall.orientation == 'N')
	{
		x_pix = fmod(wall.colision.x, 1) * texture->north.width;
		y_pix = ((double)(i - draw_start) / (double)column_height) * (double)texture->north.height;
	}
	else if (wall.orientation == 'S')
	{
		x_pix = fmod(wall.colision.x, 1) * texture->south.width;
		y_pix = ((double)(i - draw_start) / (double)column_height) * (double)texture->south.height;
	}
	else if (wall.orientation == 'E')
	{
		x_pix = fmod(wall.colision.y, 1) * texture->east.width;
		y_pix = ((double)(i - draw_start) / (double)column_height) * (double)texture->east.height;
	}
	else if (wall.orientation == 'O')
	{
		x_pix = fmod(wall.colision.y, 1) * texture->west.width;
		y_pix = ((double)(i - draw_start) / (double)column_height) * (double)texture->west.height;
	}
	x_pix -= fmod(x_pix, 1);
	if (wall.orientation == 'N')
	{
		if (get_data_pixel(frame_old->data, x, i) != get_data_pixel(texture->north.data, (int)x_pix, (int)y_pix))
		{
			put_data_pixel(frame_new->data, x, i, get_data_pixel(texture->north.data, (int)x_pix, (int)y_pix));
			put_data_pixel(frame_old->data, x, i, get_data_pixel(texture->north.data, (int)x_pix, (int)y_pix));
		}
	}
	else if (wall.orientation == 'S')
	{
		if (get_data_pixel(frame_old->data, x, i) != get_data_pixel(texture->south.data, (int)x_pix, (int)y_pix))
		{
			put_data_pixel(frame_new->data, x, i, get_data_pixel(texture->south.data, (int)x_pix, (int)y_pix));
			put_data_pixel(frame_old->data, x, i, get_data_pixel(texture->south.data, (int)x_pix, (int)y_pix));
		}
	}
	else if (wall.orientation == 'E')
	{
		if (get_data_pixel(frame_old->data, x, i) != get_data_pixel(texture->east.data, (int)x_pix, (int)y_pix))
		{
			put_data_pixel(frame_new->data, x, i, get_data_pixel(texture->east.data, (int)x_pix, (int)y_pix));
			put_data_pixel(frame_old->data, x, i, get_data_pixel(texture->east.data, (int)x_pix, (int)y_pix));
		}
	}
	else if (wall.orientation == 'O')
	{
		if (get_data_pixel(frame_old->data, x, i) != get_data_pixel(texture->west.data, (int)x_pix, (int)y_pix))
		{
			put_data_pixel(frame_new->data, x, i, get_data_pixel(texture->west.data, (int)x_pix, (int)y_pix));
			put_data_pixel(frame_old->data, x, i, get_data_pixel(texture->west.data, (int)x_pix, (int)y_pix));
		}
	}
}

static void	print_column(t_wall wall, void *mlx, void *win, int x, t_rgb *floor_rgb, t_rgb *ceilling_rgb, t_column_info *column_info, bool care_about_last_frame, t_texture *texture, t_img *frame_old, t_img *frame_new)
{
	int	i;
	int	column_height;
	int draw_start;
	int	draw_end;

	i = 0;
	column_height = (int)(SCREEN_HEIGHT / wall.distance);
	draw_start = (-column_height / 2) + (SCREEN_HEIGHT / 2);
	draw_end = (column_height / 2) + (SCREEN_HEIGHT / 2);
	while (i < SCREEN_HEIGHT)
	{
		if (i < draw_start && (i >= column_info->start || !care_about_last_frame))
		{
			if (get_data_pixel(frame_old->data, x, i) != rgb_to_put_pixel(floor_rgb))
			{
				put_data_pixel(frame_old->data, x, i, rgb_to_put_pixel(floor_rgb));
				put_data_pixel(frame_new->data, x, i, rgb_to_put_pixel(floor_rgb));
			}
		}
		else if (i >= draw_end && (i < column_info->end || !care_about_last_frame))
		{
			if (get_data_pixel(frame_old->data, x, i) != rgb_to_put_pixel(ceilling_rgb))
			{
				put_data_pixel(frame_old->data, x, i, rgb_to_put_pixel(ceilling_rgb));
				put_data_pixel(frame_new->data, x, i, rgb_to_put_pixel(ceilling_rgb));
			}
		}
		else if (i >= draw_start && i < draw_end)
			put_texture_wall(wall, column_height, x, i, draw_start, mlx, win, texture, frame_old, frame_new);
		i++;
	}
	column_info->start = draw_start;
	column_info->end = draw_end;
}

static void	reset_frame_new(t_img *frame_new)
{
	int	x;
	int y;

	y = 0;
	while (y < frame_new->height)
	{
		x = 0;
		while (x < frame_new->width)
		{
			put_data_pixel(frame_new->data, x, y, 0xFF000000);
			x++;
		}
		y++;
	}
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
		print_column(wall, info->mlx, info->win, n_column, info->conf->floor_rgb, info->conf->ceilling_rgb, &column_info[n_column], false, info->texture, info->frame_old, info->frame_new);
		n_column++;
	}
	//mlx_sync(2, info->frame->img);
	mlx_put_image_to_window(info->mlx, info->win, info->frame_new->img, 0, 0);
	reset_frame_new(info->frame_new);
	return (column_info);
}

static int	display_one_frame(void *param)
{
	t_global_info *info;

	t_wall	wall;
	double	angle;
	int		n_collumn;

	n_collumn = 0;
	info = param;
	if (!(update_player(&(info->player), info->key, info->map)))
		return (0);
	reset_frame_new(info->frame_new);
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
		print_column(wall, info->mlx, info->win, n_collumn, info->conf->floor_rgb, info->conf->ceilling_rgb, &info->column_info[n_collumn], true, info->texture, info->frame_old, info->frame_new);
		n_collumn++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->frame_new->img, 0, 0);
	return (0);
}

static void	key_hook(int keycode, t_key *key)
{
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
	info->frame_new->img = mlx_new_image(info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	info->frame_old->img = mlx_new_image(info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	info->frame_new->data.data = mlx_get_data_addr(info->frame_new->img, &info->frame_new->data.bpp, &info->frame_new->data.line_lenght, &info->frame_new->data.endian);
	info->frame_old->data.data = mlx_get_data_addr(info->frame_old->img, &info->frame_old->data.bpp, &info->frame_old->data.line_lenght, &info->frame_old->data.endian);
	info->frame_new->height = SCREEN_HEIGHT;
	info->frame_new->width = SCREEN_WIDTH;
	info->frame_old->height = SCREEN_HEIGHT;
	info->frame_old->width = SCREEN_WIDTH;
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
	texture->north.img = mlx_xpm_file_to_image(info->mlx, info->conf->texture_path[north], &info->texture->north.width, &info->texture->north.height);
	texture->north.data.data = mlx_get_data_addr(texture->north.img, &texture->north.data.bpp, &texture->north.data.line_lenght, &texture->north.data.endian);
	texture->west.img = mlx_xpm_file_to_image(info->mlx, info->conf->texture_path[west], &info->texture->west.width, &info->texture->west.height);
	texture->west.data.data = mlx_get_data_addr(texture->west.img, &texture->west.data.bpp, &texture->west.data.line_lenght, &texture->west.data.endian);
	texture->east.img = mlx_xpm_file_to_image(info->mlx, info->conf->texture_path[east], &info->texture->east.width, &info->texture->east.height);
	texture->east.data.data = mlx_get_data_addr(texture->east.img, &texture->east.data.bpp, &texture->east.data.line_lenght, &texture->east.data.endian);
	texture->south.img = mlx_xpm_file_to_image(info->mlx, info->conf->texture_path[south], &info->texture->south.width, &info->texture->south.height);
	texture->south.data.data = mlx_get_data_addr(texture->south.img, &texture->south.data.bpp, &texture->south.data.line_lenght, &texture->south.data.endian);
}

void	display(t_global_info *info)
{
	t_texture	texture;
	t_img		frame_new;
	t_img		frame_old;
	t_key		key;

	info->key = &key;
	info->texture = &texture;
	info->frame_new = &frame_new;
	info->frame_old = &frame_old;
	init_info(info);
	init_texture(&texture, info);
	mlx_hook(info->win, 02, 1L, key_hook, info->key);
	mlx_hook(info->win, 03, 1L<<1, key_hook, info->key);
	mlx_hook(info->win, 17, 1L << 17, mlx_loop_end, (void *)info->mlx);
	info->column_info = display_first_frame(info);
	if (!info->column_info)
		printf("first frame error !\n");
	mlx_loop_hook(info->mlx, display_one_frame, info);
	mlx_loop(info->mlx);
}
