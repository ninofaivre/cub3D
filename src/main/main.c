/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:25:05 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/04 18:42:09 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/*
#include <stdio.h>

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
	//print_parsing(info);
	free_info(info);
	exit(EXIT_SUCCESS);
}
