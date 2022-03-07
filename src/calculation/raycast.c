/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:30:17 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/07 23:36:07 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FOV 103
#include <header.h>

#include <stdio.h>
#include <mlx.h>

static void	print_column(double	wall_distance, void *mlx, void *win, int x)
{
	int	column_height;
	int draw_start;
	int	draw_end;

	column_height = (int)((double)1000 / wall_distance);
	draw_start = (-column_height / 2) + (1000 / 2);
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (column_height / 2) + (1000 / 2);
	if (draw_end > 1000)
		draw_end = 999;
	while (draw_start < draw_end)
	{
		mlx_pixel_put(mlx, win, 1900 - x, draw_start, 0x00FF0000);
		draw_start++;
	}
}

void	raycast(t_player player, char **map)
{
	int		n;
	double	angle;
	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, 1900, 1000, "BITE");

	angle = (double)0;
	n = 0;
	while (angle < FOV)
	{
		//printf("distance au mur de la rangée de pixel %i : %f\n", n, get_wall_distance(player.position, (player.orientation - ((double)FOV / (double)2)) + angle, map));
		print_column(get_wall_distance(player.position, (player.orientation - ((double)FOV / (double)2)) + angle, map), mlx, win, n);
		angle = ((double)FOV / (double)1900) * (double)n;
		n++;
	}
	pause();
}