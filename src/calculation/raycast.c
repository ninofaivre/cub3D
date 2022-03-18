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
#define SCREEN_WIDTH 2560
#define SCREEN_HEIGHT 1440
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

static void	put_texture_wall(t_wall wall, int column_height, int x, int draw_start, int draw_end, void *mlx, void *win, t_texture *texture, t_img *frame)
{
	t_img	*ptr_texture;
	double	x_pix;
	double	y_pix;
	double	y_step;

	x_pix = 0.0;
	y_pix = 0.0;
	if (wall.orientation == 'N')	
		ptr_texture = &texture->north;
	else if (wall.orientation == 'S')
		ptr_texture = &texture->south;
	else if (wall.orientation == 'E')
		ptr_texture = &texture->east;
	else if (wall.orientation == 'O')
		ptr_texture = &texture->west;
	if (wall.orientation == 'O' || wall.orientation == 'E')
		x_pix = fmod(wall.colision.y, 1) * ptr_texture->width;
	else if (wall.orientation == 'N' || wall.orientation == 'S')
		x_pix = fmod(wall.colision.x, 1) * ptr_texture->width;
	x_pix -= fmod(x_pix, 1);
	y_step = ((double)1 / (double)column_height) * ptr_texture->height;
	if (draw_start < 0)
	{
		y_pix = -draw_start * y_step;
		draw_start = 0;
	}
	while (draw_start < draw_end)
	{
		put_data_pixel(frame->data, x, draw_start, get_data_pixel(ptr_texture->data, (int)x_pix, (int)y_pix));
		draw_start++;
		y_pix += y_step;
	}
}

static void	put_floor_ceilling(int start, int end, int x, int rgb, t_data data)
{
	if (end < start)
		return ;
	while (start < end)
	{
		put_data_pixel(data, x, start, rgb);
		start++;
	}
}

static void	print_column(t_wall wall, void *mlx, void *win, int x, t_rgb *floor_rgb, t_rgb *ceilling_rgb, t_column_info *column_info, bool care_about_last_frame, t_texture *texture, t_img *frame)
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
		put_floor_ceilling(0, draw_start, x, rgb_to_put_pixel(floor_rgb), frame->data);
		put_floor_ceilling(draw_end, SCREEN_HEIGHT, x, rgb_to_put_pixel(ceilling_rgb), frame->data);
	}
	else
	{
		put_floor_ceilling(column_info->start, draw_start, x, rgb_to_put_pixel(floor_rgb), frame->data);
		put_floor_ceilling(draw_end, column_info->end, x, rgb_to_put_pixel(ceilling_rgb), frame->data);
	}
	put_texture_wall(wall, column_height, x, draw_start, draw_end, mlx, win, texture, frame);
	/*while (i < SCREEN_HEIGHT)
	{
		if (i < draw_start && (i >= column_info->start || !care_about_last_frame))
			put_data_pixel(frame->data, x, i, rgb_to_put_pixel(floor_rgb));//mlx_pixel_put(mlx, win, x, i, rgb_to_put_pixel(floor_rgb));
		else if (i >= draw_end && (i < column_info->end || !care_about_last_frame))
			put_data_pixel(frame->data, x, i, rgb_to_put_pixel(ceilling_rgb));//mlx_pixel_put(mlx, win, x, i, rgb_to_put_pixel(ceilling_rgb));
		else if (i >= draw_start && i < draw_end)
			put_texture_wall(wall, column_height, x, i, draw_start, mlx, win, texture, frame);
		i++;
	}*/
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
		print_column(wall, info->mlx, info->win, n_column, info->conf->floor_rgb, info->conf->ceilling_rgb, &column_info[n_column], false, info->texture, info->frame);
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
		print_column(wall, info->mlx, info->win, n_collumn, info->conf->floor_rgb, info->conf->ceilling_rgb, &info->column_info[n_collumn], true, info->texture, info->frame);
		n_collumn++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->frame->img, 0, 0);
	gettimeofday(&time_after_frame, NULL);
	printf("temps de rendu d'une frame : %ld ms, fps : %ld\n", (time_after_frame.tv_usec - time_before_frame.tv_usec) / 1000, 1000000 / (time_after_frame.tv_usec - time_before_frame.tv_usec));
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
	info->frame->img = mlx_new_image(info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	info->frame->data.data = mlx_get_data_addr(info->frame->img, &info->frame->data.bpp, &info->frame->data.line_lenght, &info->frame->data.endian);
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
	t_img		frame;
	t_key		key;

	info->key = &key;
	info->texture = &texture;
	info->frame = &frame;
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
