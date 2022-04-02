/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:25:05 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/10 22:45:00 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <mlx.h>
/*
static void	print_parsing(t_global_info *info)
{
	printf("conf :\n\npath :\n");
	print_str_tab(info->conf->texture_path);
	printf("rgb_floor :\nr : %i\ng : %i\nb : %i\n", info->conf->floor_rgb->r, info->conf->floor_rgb->g, info->conf->floor_rgb->b);
	printf("ceilling_floor :\nr : %i\ng : %i\nb : %i\n", info->conf->ceilling_rgb->r, info->conf->ceilling_rgb->g, info->conf->ceilling_rgb->b);
}*/

int	main(int argc, char **argv)
{
	t_global_info	*info;

	info = parsing(argc, argv);
	if (!info)
		exit(EXIT_FAILURE);
	display(info);
	//print_parsing(info);
	//printf("%f\n", get_wall_distance(info->player.position, (double)135, info->map->content));
	mlx_do_key_autorepeatoff(info->mlx);
	mlx_do_key_autorepeaton(info->mlx);
	free_info(info);
	printf("fin normal du programme atteinte");
	exit(EXIT_SUCCESS);
}
