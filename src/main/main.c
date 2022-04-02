/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:25:05 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/02 19:00:42 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "calculation.h"
#include "parsing.h"
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>
#include <mlx.h>

static void	start_raycast(t_global_info *info)
{
	t_put_texture	put_texture;
	t_texture		texture;
	t_img			frame;
	t_key			key;

	info->key = &key;
	info->texture = &texture;
	info->frame = &frame;
	info->put_texture = &put_texture;
	init_raycast_info(info);
	init_texture(&texture, info);
	mlx_hook(info->win, 02, 1L, key_hook_press, info->key);
	mlx_hook(info->win, 03, 1L << 1, key_hook_release, info->key);
	mlx_hook(info->win, 17, 1L << 17, mlx_loop_end, (void *)info->mlx);
	info->column_info = init_column_info();
	if (!info->column_info)
		printf("first frame error !\n");
	mlx_loop_hook(info->mlx, display_one_frame, info);
	mlx_loop(info->mlx);
}

int	main(int argc, char **argv)
{
	t_global_info	*info;

	info = parsing(argc, argv);
	if (!info)
		exit(EXIT_FAILURE);
	start_raycast(info);
	free_info(info);
	printf("fin normal du programme atteinte");
	exit(EXIT_SUCCESS);
}
