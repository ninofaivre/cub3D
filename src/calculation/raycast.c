/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:30:17 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/09 21:35:27 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FOV 60
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#include <header.h>

#include <stdio.h>
#include <mlx.h>
#include <math.h>

typedef	struct s_key_hook
{
	void		*mlx;
	void		*win;
	t_player	*player;
	char		**map;
}	t_key_hook;

static void	print_column(double	wall_distance, void *mlx, void *win, int x)
{
	int	column_height;
	int draw_start;
	int	draw_end;

	column_height = (int)((double)SCREEN_HEIGHT / wall_distance);
	draw_start = (-column_height / 2) + (SCREEN_HEIGHT / 2);
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (column_height / 2) + (SCREEN_HEIGHT / 2);
	if (draw_end > SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	while (draw_start < draw_end)
	{
		mlx_pixel_put(mlx, win, SCREEN_WIDTH - x, draw_start, 0x00FF0000);
		draw_start++;
	}
}

static void	display_one_frame(void *mlx, void *win, t_player player, char **map)
{
	double	angle;
	double	beta;
	double	cos_beta;
	int	n_collumn;

	n_collumn = 0;
	mlx_clear_window(mlx, win);
	while (n_collumn < SCREEN_WIDTH)
	{
		angle = ((double)(player.orientation - ((double)FOV / (double)2)) + (double)((double)n_collumn * ((double)FOV / (double)SCREEN_WIDTH)));
		if (angle < 0)
			angle = (double)360 + angle;
		if (angle > 360)
			angle  = angle - (double)360;
		beta = (double)angle - (double)player.orientation;
		cos_beta = (double)cos(beta * (M_PI / (double)180));
		print_column((get_wall_distance(player.position, angle, map) * cos_beta), mlx, win, n_collumn);
		n_collumn++;
	}
}

static void	moove(t_player *player)
{
	printf("player position : %f, %f\n", player->position.x, player->position.y);
	if (player->orientation >= 0 && player->orientation <= 90)
	{
		player->position.x += cos(player->orientation * (M_PI / (double)180)) * (double)0.1;
		player->position.y -= sin(player->orientation * (M_PI / (double)180)) * (double)0.1;
	}
	printf("player position : %f, %f\n", player->position.x, player->position.y);
}

static void	key_hook(int keycode, t_key_hook *key)
{
	printf("orientation : %f\n", key->player->orientation);
	key->player->orientation = key->player->orientation + ((keycode == 65363) * 1) + ((keycode == 65361) * -1);
	if (key->player->orientation == 360)
		key->player->orientation = 0;
	if (key->player->orientation == -1)
		key->player->orientation = 359;
	if (keycode == 122)
		moove(key->player);
	if (keycode == 115)
		key->player->position.y += (double)0.1;
	display_one_frame(key->mlx, key->win, *(key->player), key->map);
}

void	display(t_player *player, char **map)
{
	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "lkqsdflkskldfqk");
	t_key_hook	key;

	key.mlx = mlx;
	key.win = win;
	key.player = player;
	key.map = map;
	mlx_hook(win, 02, 1L, key_hook, &key);
	display_one_frame(mlx, win, *player, map);
	mlx_do_key_autorepeaton(mlx);
	mlx_loop(mlx);
}